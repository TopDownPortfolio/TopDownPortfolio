#include "C_MakeHeightMap.h"
#include "EditorModeManager.h"
#include "EditorModes.h"
#include "LevelEditor.h"   
#include "Landscape.h"
#include "LandscapeComponent.h"
#include "LandscapeInfo.h"
#include "LandscapeEdit.h"
#include "EditorAssetLibrary.h"

void UC_MakeHeightMap::OnRegister()
{
	UActorComponent::OnRegister();
}

void UC_MakeHeightMap::PostEditChangeProperty(FPropertyChangedEvent& PropertyChangedEvent)
{
	UActorComponent::PostEditChangeProperty(PropertyChangedEvent);

	bool bRemake{};
	if (m_bGenerateHeightMap)
	{
		E_GenerateHeightMap();
		bRemake = true;
	}
	if (m_bExportHeightMap)
	{
		E_ExportHeightMap();
	}
	if (m_bImportHeightMap) 
	{
		E_ImportHeightMap();
	}
	if (bRemake)
	{
		E_UpdateLandscape();
	}
}

bool UC_MakeHeightMap::E_Init_SetLandscapeData()
{
	m_pLandscape = Cast<ALandscape>(GetOwner());
	if (!m_pLandscape)
		return false;
	m_pLandscapeInfo = m_pLandscape->GetLandscapeInfo();
	return m_pLandscapeInfo != nullptr;
}

bool UC_MakeHeightMap::E_Init_SetData()
{
	if (!E_Init_SetLandscapeData())
		return false;
	int32 nComponnetSize = m_pLandscapeInfo->ComponentSizeQuads;
	m_pLandscapeInfo->GetLandscapeExtent(m_fLandScapeSize);
	int32 nCount = m_fLandScapeSize.Max.X / nComponnetSize;
	m_fLandScapeSize.Max.X = nCount * (nComponnetSize + 1) + 1;
	m_fLandScapeSize.Max.Y = nCount * (nComponnetSize + 1) + 1;
	m_nStride = (m_fLandScapeSize.Max.X - m_fLandScapeSize.Min.X) + 1;
	m_nMapSize = m_nStride * m_nStride + m_nStride + 1;
	m_arHeightData.Init(LandscapeDataAccess::MidValue, m_nMapSize);
	return true;
}

void UC_MakeHeightMap::E_GenerateHeightMap()
{
	if (!E_Init_SetData())
		return;
	E_Logic(m_fLandScapeSize.Max.X - m_fLandScapeSize.Min.X);
	FIntRect fData{};
	m_pLandscapeInfo->GetLandscapeExtent(fData);
	FLandscapeEditDataInterface LandscapeEdit{ m_pLandscapeInfo };
	LandscapeEdit.SetHeightData(fData.Min.X, fData.Min.Y, fData.Max.X, fData.Max.Y, m_arHeightData.GetData(), m_nStride, false);
	m_bGenerateHeightMap = false;
}

void UC_MakeHeightMap::E_UpdateLandscape()
{ 
	if (!E_Init_SetLandscapeData())
		return;
	bool bHasLandscapeLayersContent = m_pLandscape && m_pLandscape->HasLayersContent();
	m_pLandscape->Modify();
	m_pLandscapeInfo->ClearDirtyData();
	m_pLandscapeInfo->Modify();
	for (ULandscapeComponent* pLandComp : m_pLandscape->LandscapeComponents)
	{
		pLandComp->UpdateCachedBounds();
		pLandComp->UpdateBounds();
		pLandComp->MarkRenderStateDirty();
		if (!bHasLandscapeLayersContent)
		{
			ULandscapeHeightfieldCollisionComponent* CollisionComp = pLandComp->GetCollisionComponent();
			if (CollisionComp)
			{
				CollisionComp->MarkRenderStateDirty();
				CollisionComp->RecreateCollision();
			}
		}
		pLandComp->RequestHeightmapUpdate(false, true);
	}
	m_pLandscape->ForceUpdateLayersContent(false);
	//m_pLandscape->flush
	//
}

// 구현 중 해당 함수 처음 호출 시 Terrain 설정 버그가 일어나서 수정이 필요
void UC_MakeHeightMap::E_ImportHeightMap()
{
	if (!E_Init_SetLandscapeData())
		return;
	m_pLandscape->Modify();
	
	FIntRect fData{};
	m_pLandscapeInfo->GetLandscapeExtent(fData);

	FString FilePath = E_GetFilePath(m_ImportFileName);

	TArray<FLandscapeImportLayerInfo> importLandInfo;
	TMap<FGuid, TArray<uint16>> InImportHeightData{};
	TMap<FGuid, TArray<FLandscapeImportLayerInfo>>InImportMaterialLayerInfos{};

	InImportHeightData.Add(FGuid(), MoveTemp(m_arHeightData));
	InImportMaterialLayerInfos.Add(FGuid(), MoveTemp(importLandInfo));
	TArray<UActorComponent*> Components;

	bool bValue = m_pLandscape->bCanHaveLayersContent;
	m_pLandscape->bCanHaveLayersContent = false;
	m_pLandscape->GetComponents(UActorComponent::StaticClass(), Components);
	for (UActorComponent* Component : Components)
	{
		ULandscapeComponent* LandscapeComp = Cast<ULandscapeComponent>(Component);
		if (LandscapeComp)
		{
			LandscapeComp->DestroyComponent();
		}
	}
	m_pLandscape->Import(m_pLandscape->GetLandscapeGuid(), fData.Min.X, fData.Min.Y, fData.Max.X, fData.Max.Y,
		m_pLandscapeInfo->ComponentNumSubsections, m_pLandscapeInfo->SubsectionSizeQuads,
		InImportHeightData, *FilePath, InImportMaterialLayerInfos,
		ELandscapeImportAlphamapType::Additive
	);
	m_pLandscape->bCanHaveLayersContent = bValue;
	m_bImportHeightMap = false;
	//m_pLandscapeInfo->ForceLayersFullUpdate();
}

void UC_MakeHeightMap::E_ExportHeightMap()
{
	if (!E_Init_SetLandscapeData())
		return;
	
	FString FilePath = E_GetFilePath(m_ExportFileName);
	UEditorAssetLibrary::DeleteAsset(FilePath);
	m_pLandscapeInfo->ExportHeightmap(FilePath);
	m_bExportHeightMap = false;
}

int UC_MakeHeightMap::E_Logic(int nDist)
{
	if (nDist <= 0)
		return 0;
	int Half = nDist / 2;

	for (int i = Half; i <= m_fLandScapeSize.Max.X; i += nDist)
	{
		for (int j = Half; j <= m_fLandScapeSize.Max.Y; j += nDist)
		{
			E_CalCul(i, j, m_nDX, m_nDY, Half);
		}
	}

	for (int i = Half; i <= m_fLandScapeSize.Max.X; i += nDist)
	{
		for (int j = 0; j <= m_fLandScapeSize.Max.Y; j += nDist)
		{
			E_CalCul(i, j, m_nSX, m_nSY, Half);
		}
	}
	for (int i = 0; i <= m_fLandScapeSize.Max.X; i += nDist)
	{
		for (int j = Half; j <= m_fLandScapeSize.Max.Y; j += nDist)
		{
			E_CalCul(i, j, m_nSX, m_nSY, Half);
		}
	}
	return 1 + E_Logic(Half);
}

void UC_MakeHeightMap::E_CalCul(int X, int Y, const int* dX, const int* dY, uint16 S)
{
	uint16* pCurrent = E_GetHeightMap(X, Y);
	if (!pCurrent)
		return;
	int nAVG{};
	int nCount{};
	for (int i = 0; i < 4; i++)
	{
		uint16* pValue = E_GetHeightMap(X + dX[i] * S, Y + dY[i] * S);
		if (pValue)
		{
			nAVG += *pValue;
			nCount++;
		}
	}
	if (nCount == 0)
		return;
	*pCurrent = nAVG / nCount;
	float Height = E_GetRoughnessFactor(S);
	*pCurrent += Height;
}

int UC_MakeHeightMap::E_GetArrIndex(int X, int Y)
{
	return (Y - m_fLandScapeSize.Min.Y) * m_nStride + (X - m_fLandScapeSize.Min.X);
}

uint16* UC_MakeHeightMap::E_GetHeightMap(int x, int y)
{
	int nIndx = E_GetArrIndex(x, y);
	if (!m_arHeightData.IsValidIndex(nIndx))
		return nullptr;
	return 	&m_arHeightData[nIndx];
}

float UC_MakeHeightMap::E_GetRoughnessFactor(uint16 S)
{
	float nValue = S * m_fFactor; 
	if (abs(nValue) > 8192.f)
	{
		nValue = nValue / abs(nValue) * 8192.f;
	}
	float nReuslt = FMath::RandRange(-nValue, nValue);
	return nReuslt;
}

FString UC_MakeHeightMap::E_GetFilePath(FString& strFileName)
{
	return FPaths::ProjectContentDir() + TEXT("/03_Map/HeightMap/Texture/") + strFileName + TEXT(".png");
}

