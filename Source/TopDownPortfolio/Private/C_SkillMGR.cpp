#include "C_SkillMGR.h"
#include "A_PlayerController.h"
#include "A_Character_Base.h"
#include "D_DataTable.h"
#include "C_MontageMGR.h"
#include "C_StatusMGR.h"

UC_SkillMGR::UC_SkillMGR() :
	UActorComponent{}, m_pOwner{}, m_pDataTable{}, m_arSkillData{}, m_arIndex{}, m_sSrc{},
	m_arMaxTime{}, m_arCoolTime{}, On_ActionActive{}
{
	PrimaryComponentTick.bCanEverTick  = true;
	D_DataTable cData{};
	m_pDataTable = cData.E_Default_Skiil();
	for (uint8 i = (uint8)FE_SkillID::E_NONE; i < (uint8)FE_SkillID::E_EnumMAX; i++)
	{
		m_arIndex[i].Init(0, 4);
		m_arMaxTime[i] = 4;
		m_arCoolTime[i] = -1;
	}
}


void UC_SkillMGR::BeginPlay()
{
	UActorComponent::BeginPlay();
	AA_PlayerController* pController = Cast<AA_PlayerController>(GetOwner());
	if (!pController || pController->AcknowledgedPawn == nullptr)
	{
		DestroyComponent();
		return;
	}

	m_pOwner = Cast<AA_Character_Base>(pController->AcknowledgedPawn);
	// TODO : 아래의 E_SetSkillIndex 설정은 임시 이고 추후 DT 추가
	E_SetSkillIndex(FE_SkillID::E_01, 1, 1);
	E_SetSkillIndex(FE_SkillID::E_01, 2, 2);
	E_SetSkillIndex(FE_SkillID::E_01, 3, 3);
	E_SetSkillIndex(FE_SkillID::E_02, 1, 1);
	E_SetSkillIndex(FE_SkillID::E_02, 2, 2);
	E_SetSkillIndex(FE_SkillID::E_02, 3, 3);
	E_SetSkillIndex(FE_SkillID::E_03, 1, 1);
	E_SetSkillIndex(FE_SkillID::E_03, 2, 2);
	E_SetSkillIndex(FE_SkillID::E_03, 3, 3);

	if (m_pDataTable)
	{
		TArray< FS_SkillData*> arData{};
		m_pDataTable->GetAllRows< FS_SkillData>("", arData);
		m_arSkillData.Init(nullptr, (uint8)FE_SkillID::E_EnumMAX + 1);
		for (FS_SkillData*& pData : arData)
		{
			m_arSkillData[(uint8)pData->eSkillID] = pData;
		}
	}
}

void UC_SkillMGR::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	for (uint8 i = (uint8)FE_SkillID::E_NONE; i < (uint8)FE_SkillID::E_EnumMAX; i++)
	{
		if (m_arCoolTime[i] > 0)
			m_arCoolTime[i] -= DeltaTime;
		if (m_arCoolTime[i] < 0)
			m_arCoolTime[i] = 0;
	}
}

void UC_SkillMGR::E_SetSkillIndex(FE_SkillID eSkillID, int nIndex, int nValue)
{
	uint8 eIndex = (uint8)eSkillID;
	if (m_arIndex[eIndex].Num() > nIndex)
		m_arIndex[(uint8)eSkillID][nIndex] = nValue;
}

bool UC_SkillMGR::E_Action(FE_SkillID eID)
{
	S_CurrentData sDst{};
	sDst.eSkillID = eID;
	sDst.nSkillIndex = (uint8)sDst.eSkillID;
	if (m_arSkillData.Num() <= sDst.nSkillIndex || !m_arSkillData[sDst.nSkillIndex])
		return false;
	FE_MontageID eMontageID = m_arSkillData[sDst.nSkillIndex]->eMontageID;
	FE_StatusID eStatusID = FE_StatusID::E_MP;
	float fStatus = -m_arSkillData[sDst.nSkillIndex]->fConsumMP;
	UC_MontageMGR* pMontageMGR = m_pOwner->E_GetMontageMGR();
	UC_StatusMGR* pStatusMGR= m_pOwner->E_GetStatusMGR();

	// TODO : 추후 콤보 입력을 처리하기 위해 삭제 보류
	//if (m_sSrc.eSkillID == sDst.eSkillID)
	//{
	//	sDst.nPlayIndex = m_sSrc.nPlayIndex;
	//	sDst.nIndex = m_sSrc.nIndex;
	//}
	bool bResult = pMontageMGR->E_CheckPlayable(eMontageID, sDst.nPlayIndex);
	if (m_arCoolTime[sDst.nSkillIndex] > 0.0f)
		bResult = false;
	if (bResult && pStatusMGR->E_CheckAdd(eStatusID, fStatus))
	{
		m_arCoolTime[sDst.nSkillIndex] = m_arMaxTime[sDst.nSkillIndex];
		E_Copy(m_sSrc, sDst);
		m_pOwner->E_SubState(FE_StateType::E_IsTravel);
		pStatusMGR->E_AddStatus_Current(eStatusID, fStatus);
		E_PlayNextMontage();
	}
	if (On_ActionActive.IsBound())
	{
		On_ActionActive.Broadcast(sDst.eSkillID, bResult);
	}
	return bResult;
}

bool UC_SkillMGR::E_PlayNextMontage()
{
	FE_MontageID eMontageID = m_arSkillData[m_sSrc.nSkillIndex]->eMontageID;
	UC_MontageMGR* pMontageMGR = m_pOwner->E_GetMontageMGR();
	if (!pMontageMGR)
		return false;
	pMontageMGR->E_SetMontageData(eMontageID, m_sSrc.nPlayIndex);
	pMontageMGR->E_PlayMontage();
	return true;
}

bool UC_SkillMGR::E_SetNextMontage()
{
	m_sSrc.nIndex++;
	if (m_sSrc.nIndex >= m_arIndex[m_sSrc.nSkillIndex].Num())
		m_sSrc.nIndex = 0;
	m_sSrc.nPlayIndex = m_arIndex[m_sSrc.nSkillIndex][m_sSrc.nIndex];
	return m_sSrc.nIndex != 0;
}
