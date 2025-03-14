#include "C_MakeHeightMap.h"
#include "EditorModeManager.h"
#include "EditorModes.h"
#include "LevelEditor.h"   
#include "Landscape.h"
#include "LandscapeComponent.h"
#include "LandscapeInfo.h"
#include "LandscapeEdit.h"
#include "LandscapeSubsystem.h"
#include "Editor/LandscapeEditor/Private/LandscapeEdMode.h"
#include "Editor/LandscapeEditor/Public/LandscapeEditorModule.h"
#include "Editor/LandscapeEditor/Public/LandscapeImportHelper.h"
#include "Editor/LandscapeEditor/Public/LandscapeEditorObject.h"
#include "Editor/LandscapeEditor/Private/LandscapeEditorDetailCustomization_Base.h"

void UC_MakeHeightMap::OnRegister()
{
	UActorComponent::OnRegister();	
	if (!m_bMakeTexture)
	{
		E_SetInit();
	}
}

void UC_MakeHeightMap::PostEditChangeProperty(FPropertyChangedEvent& PropertyChangedEvent)
{
	UActorComponent::PostEditChangeProperty(PropertyChangedEvent);
	if (m_bMakeTexture)
	{
		//if (ULandscapeInfo* LandscapeInfo = m_pLandscapeInfo)
		//{
		//	FIntRect LandscapeExtent;
		//	LandscapeInfo->GetLandscapeExtent(LandscapeExtent);

		//	LandscapeExtent.Max.X += 1;
		//	LandscapeExtent.Max.Y += 1;

		//	FGuid CurrentLayerGuid = m_pLandscape->GetGridGuid();
		//	//	guid->GetCurrentLayerGuid();

		//	const ELandscapeLayerPaintingRestriction PaintRestriction = ELandscapeLayerPaintingRestriction::None;

		//	ELandscapeImportTransformType TransformType = ELandscapeImportTransformType::ExpandOffset; //  LandscapeEdMode->UISettings->ImportType;

		//	FVector LocalGizmoPosition = LandscapeInfo->GetLandscapeProxy()->LandscapeActorToWorld().InverseTransformPosition(m_pLandscape->GetActorLocation());
		//	FIntPoint LocalGizmoPoint = FIntPoint(FMath::FloorToInt32(LocalGizmoPosition.X), FMath::FloorToInt32(LocalGizmoPosition.Y));

		//	// Update Gizmo Position if we exit and comeback into tool
		//	//LandscapeEdMode->UISettings->ImportLandscape_GizmoLocalPosition = LocalGizmoPoint;

		//	FIntRect ImportRegion = LandscapeExtent;
		//	FIntPoint ImportOffset(0, 0);
		//	if (TransformType == ELandscapeImportTransformType::ExpandOffset)
		//	{
		//		ImportOffset = LocalGizmoPoint - FIntPoint(LandscapeExtent.Min.X, LandscapeExtent.Min.Y);
		//	}
		//	else if (TransformType == ELandscapeImportTransformType::None)
		//	{
		//		ImportRegion = FIntRect(
		//			LocalGizmoPoint.X,
		//			LocalGizmoPoint.Y,
		//			LocalGizmoPoint.X + LandscapeExtent.Max.X,
		//			LocalGizmoPoint.Y + LandscapeExtent.Max.Y);
		//	}
		//	#if WITH_EDITOR
		//	FEdModeLandscape* LandscapeEdMode = (FEdModeLandscape*)GLevelEditorModeTools().GetActiveMode(FBuiltinEditorModes::EM_Landscape);;
		//	//if (!m_LoadHeight.Get())
		//	//	m_LoadHeight.LoadSynchronous();
		//	//m_LoadHeight.Get()->GetDefaultConfigFilename()
		//	if (LandscapeEdMode )// && m_LoadHeight.Get())
		//	{
		//		//LandscapeEdMode->ImportHeightData(LandscapeInfo, CurrentLayerGuid,
		//		//	m_LoadHeight, LandscapeExtent,
		//		//	TransformType, ImportOffset, PaintRestriction, LandscapeEdMode->UISettings->bFlipYAxis);
		//	}
		//	#endif
		//		//ImportDataInternal<uint16>(LandscapeInfo, FilePath, NAME_None, true, false, ImportRegion, TransformType, ImportOffset, [LandscapeInfo, CurrentLayerGuid, PaintRestriction](int32 MinX, int32 MinY, int32 MaxX, int32 MaxY, const TArray<uint16>& Data)
		//	//	{
		//	//		ALandscape* Landscape = LandscapeInfo->LandscapeActor.Get();
		//	//		FScopedSetLandscapeEditingLayer Scope(Landscape, CurrentLayerGuid, [&] { check(Landscape); Landscape->RequestLayersContentUpdate(ELandscapeLayerUpdateMode::Update_Heightmap_All); });
		//	//
		//	//		//FScopedTransaction Transaction(LOCTEXT("Undo_ImportHeightmap", "Importing Landscape Heightmap"));
		//	//
		//	//		FHeightmapAccessor<false> HeightmapAccessor(LandscapeInfo);
		//	//		HeightmapAccessor.SetData(MinX, MinY, MaxX, MaxY, Data.GetData());
		//	//	});
		//}
			m_nCount = 0;
			m_bMakeTexture = false;
	}
	else
	{
		E_GenerateHeightMap();
		E_ExportHeightmapToPNG();
	}
	E_UpdateLandscape();
}

void UC_MakeHeightMap::E_SetInit()
{
	m_pLandscape = Cast<ALandscape>( GetOwner());
	if (!m_pLandscape)
		return;
	m_pLandscapeInfo = m_pLandscape->GetLandscapeInfo();
	if (!m_pLandscapeInfo)
		return;
	int32 nComponnetSize = m_pLandscapeInfo->ComponentSizeQuads;
	m_pLandscapeInfo->GetLandscapeExtent(m_fLandScapeSize);
	int32 nCount = m_fLandScapeSize.Max.X / nComponnetSize;
	m_fLandScapeSize.Max.X = nCount * (nComponnetSize + 1) + 1;
	m_fLandScapeSize.Max.Y = nCount * (nComponnetSize + 1) + 1;
	m_nStride = (m_fLandScapeSize.Max.X - m_fLandScapeSize.Min.X) + 1;
	m_nMapSize = m_nStride * m_nStride + m_nStride + 1;
	m_arHeightData.Init(LandscapeDataAccess::MidValue, E_GetMapSize());
}

void UC_MakeHeightMap::E_GenerateHeightMap()
{
	if (!m_pLandscape || !m_pLandscapeInfo)
		return;
	FLandscapeEditDataInterface LandscapeEdit{ m_pLandscapeInfo };
	FIntRect fData{};
	m_pLandscapeInfo->GetLandscapeExtent(fData);
	//LandscapeEdit.GetHeightDataFast(fData.Min.X, fData.Min.Y, fData.Max.X, fData.Max.Y, m_arHeightData.GetData(), m_nStride);
	m_fAlpha = m_fLandScapeSize.Max.X - m_fLandScapeSize.Min.X;
	E_Logic(m_fLandScapeSize.Max.X - m_fLandScapeSize.Min.X);
	for (ULandscapeComponent* Component : m_pLandscape->LandscapeComponents)
	{
		if (Component)
		{
			Component->MarkRenderStateDirty();
		}
	}
	LandscapeEdit.SetHeightData(fData.Min.X, fData.Min.Y, fData.Max.X, fData.Max.Y, m_arHeightData.GetData(), m_nStride, false);
	LandscapeEdit.RecalculateNormals();
}

void UC_MakeHeightMap::E_UpdateLandscape()
{
	if (!m_pLandscape || !m_pLandscapeInfo)
		return;
	//for (ULandscapeComponent* Component : m_pLandscape->LandscapeComponents)
	//{
	//	if (Component)
	//	{
	//		Component->MarkRenderStateDirty();
	//		Component->RequestHeightmapUpdate(true, true);
	//		Component->UpdateCachedBounds(true);
	//		Component->UpdateNavigationBounds();
	//		Component->PostLoad();
	//	}
	//}
	//
	//for (ULandscapeHeightfieldCollisionComponent* Component : m_pLandscape->CollisionComponents)
	//{
	//	if (Component)
	//	{
	//		Component->RecreateCollision();
	//		Component->RecreateRenderState_Concurrent();
	//	}
	//}
	//m_pLandscape->FlushGrassComponents();
	//m_pLandscape->RecreateCollisionComponents();
	m_pLandscapeInfo->ForceLayersFullUpdate();
	//m_pLandscapeInfo->Reset();
}

void UC_MakeHeightMap::E_ExportHeightmapToPNG()
{
	if (!m_pLandscapeInfo) 
		return;
	FString FilePath = FPaths::ProjectContentDir() + TEXT("/03_Map/HeightMap/Texture/") + m_strFileName + TEXT("_") + FString::FromInt(m_nCount) +  TEXT(".png");
	m_nCount++;
	m_pLandscapeInfo->ExportHeightmap(FilePath);
	m_bMakeTexture = false;
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
	//m_fAlpha *= m_fFactor;
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
	*pCurrent += Height; // LandscapeDataAccess::GetTexHeight(Height);
}

int32 UC_MakeHeightMap::E_GetMapSize()
{
	return m_nMapSize;
}

int UC_MakeHeightMap::E_GetArrIndex(int X, int Y)
{
	//(LandscapeY - Y1)* Stride + (LandscapeX - X1)
	return (Y - m_fLandScapeSize.Min.Y) * m_nStride + (X - m_fLandScapeSize.Min.X);
}

bool UC_MakeHeightMap::E_GetHeightValue(int x, int y, uint16& Height)
{
	Height = LandscapeDataAccess::MidValue;
	int nIndx = E_GetArrIndex(x, y);
	if (!m_arHeightData.IsValidIndex(nIndx))
		return false;
	Height = m_arHeightData[nIndx];
	return true;
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
	float nValue = S / 2* m_fFactor; 
	float nReuslt = FMath::RandRange(-nValue, nValue);
	return nReuslt;
}