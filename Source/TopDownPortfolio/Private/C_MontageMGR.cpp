#include "C_MontageMGR.h"
#include "GameFramework/Character.h"
#include "Components/SkeletalMeshComponent.h"
#include "Animation/AnimInstance.h"
#include "D_DataTable.h"

UC_MontageMGR::UC_MontageMGR() : 
	UActorComponent{}, m_arMontageData{}, m_pInstance{}, m_pCurrentData{}, m_sPlayData{}, m_eCurrentID{}, m_pDataTable{}, m_bIsPlaying{}, m_bCanPlay {}, m_bIsInterruptable{}
{
	PrimaryComponentTick.bCanEverTick = false;
	m_pDataTable = UD_DataTable::E_GetDefault_DataTable(N_DefaultPath::E_Montage);
	m_bCanPlay = true;
	for (uint8 i = (uint8)FE_MontageID::E_NONE ; i < (uint8)FE_MontageID::E_EnumMAX; i++)
	{
		m_arMontageData[i].Init({}, 10);
	}
}

void UC_MontageMGR::BeginPlay()
{
	UActorComponent::BeginPlay();
	if (!Cast<ACharacter>(GetOwner()))
	{
		DestroyComponent(); 
		return;
	}
	Cast<ACharacter>(GetOwner())->GetMesh()->OnAnimInitialized.AddDynamic(this, &UC_MontageMGR::E_Bind);
	E_Bind();
	if (m_pDataTable)
	{
		TArray< FS_MontageData*> arData{};
		m_pDataTable->GetAllRows< FS_MontageData>("", arData);
		for (FS_MontageData*& pData : arData)
		{
			m_arMontageData[(uint8)pData->eID][pData->nIndex]= pData;
		}
	}
}

FS_MontageData* UC_MontageMGR::E_GetMontageData(FE_MontageID eID, int nIndex)
{
	FS_MontageData* pResult{};
	uint8 eIndex = (uint8)eID;
	if (m_arMontageData[eIndex].Num() > nIndex)
		pResult = m_arMontageData[eIndex][nIndex];
	return pResult;
}


void UC_MontageMGR::E_Started(UAnimMontage* pMontage)
{
	m_bCanPlay = false;
	m_bIsPlaying = true;
}

void UC_MontageMGR::E_Ended(UAnimMontage* pMontage, bool bInterrupted)
{
	m_bIsInterruptable = bInterrupted;
	m_pCurrentData = nullptr;
	m_bIsPlaying = m_bIsInterruptable;
}

void UC_MontageMGR::E_BlendingOutStarted(UAnimMontage* pMontage, bool bInterrupted)
{
	m_bIsInterruptable = bInterrupted;
}

void UC_MontageMGR::E_BlendedInEnded(UAnimMontage* pMontage)
{
}

void UC_MontageMGR::E_Bind()
{
	m_pInstance = Cast<ACharacter>(GetOwner())->GetMesh()->GetAnimInstance();
	if (!m_pInstance)
		return;
	m_pInstance->OnMontageStarted.AddDynamic(this, &UC_MontageMGR::E_Started);
	m_pInstance->OnMontageBlendedIn.AddDynamic(this, &UC_MontageMGR::E_BlendedInEnded);
	m_pInstance->OnMontageBlendingOut.AddDynamic(this, &UC_MontageMGR::E_BlendingOutStarted);
	m_pInstance->OnMontageEnded.AddDynamic(this, &UC_MontageMGR::E_Ended);
}

bool UC_MontageMGR::E_Play(FE_MontageID eID, int nIndex)
{
	bool bResult{};
	if (E_CheckPlayable(eID, nIndex))
	{
		E_SetMontageData(eID, nIndex);
		E_PlayMontage();
		E_Jump2Section();
	}
	return bResult;
}

bool UC_MontageMGR::E_CheckPlayable(FE_MontageID eID, int nIndex)
{
	FS_MontageData* pDst = E_GetMontageData(eID, nIndex);
	if (!pDst || !m_pInstance)
		return false;
	if (m_bCanPlay)
		return true;
	bool bResult = !m_bIsPlaying;
	if (!bResult)
	{
		if (m_pCurrentData)
		{
			bResult = false;
			if (m_pCurrentData->eID == eID && m_pCurrentData->nIndex < pDst->nIndex)
				bResult = true;
		}
	}
	return bResult;
}

void UC_MontageMGR::E_PlayMontage_Implementation()
{
	m_pInstance->Montage_Play(m_pCurrentData->pMontage, m_sPlayData.fPlaySpeed);
}

void UC_MontageMGR::E_Jump2Section_Implementation()
{
	m_pInstance->Montage_JumpToSection(m_sPlayData.strSection, m_pCurrentData->pMontage);
}


