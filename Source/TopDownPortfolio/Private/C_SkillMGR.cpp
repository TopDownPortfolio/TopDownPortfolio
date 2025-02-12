#include "C_SkillMGR.h"
#include "A_Character_Base.h"
#include "D_DataTable.h"
#include "C_MontageMGR.h"
#include "C_StatusMGR.h"

UC_SkillMGR::UC_SkillMGR() :
	UActorComponent{}, m_pOwner{}, m_pDataTable{}, m_arSkillData{}, m_arIndex{}, m_sSrc{}
{
	PrimaryComponentTick.bCanEverTick  = false;
	D_DataTable cData{};
	m_pDataTable = cData.E_Default_Skiil();
}


void UC_SkillMGR::BeginPlay()
{
	UActorComponent::BeginPlay();
	m_pOwner = Cast<AA_Character_Base> (GetOwner());
	if (!m_pOwner)
	{
		DestroyComponent();
		return;
	}

	// TODO : 아래의 m_arIndex 설정은 임시 이고 추후 Interaction 추가
	m_arIndex[0].Init(0, 1);
	m_arIndex[1].Init(0, 4);
	m_arIndex[1][0] = 0; 
	m_arIndex[1][1] = 1; 
	m_arIndex[1][2] = 2; 
	m_arIndex[1][3] = 3; 
	m_arIndex[2].Init(0, 3);
	m_arIndex[2][0] = 0;
	m_arIndex[2][1] = 1;
	m_arIndex[2][2] = 5;
	m_arIndex[3].Init(0, 3);
	m_arIndex[3][0] = 0;
	m_arIndex[3][1] = 1;
	m_arIndex[3][2] = 6;
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
	if (bResult && pStatusMGR->E_CheckAdd(eStatusID, fStatus))
	{
		E_Copy(m_sSrc, sDst);
		m_pOwner->E_SubState(FE_StateType::E_IsTravel);
		pStatusMGR->E_AddStatus_Current(eStatusID, fStatus);
		E_PlayNextMontage();
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
	// 아래 if는 버그 fix를 위한 임시
	// TODO : 따로 함수로 둬서 호출하게 할지 SetNext에 포함 시킬지 고민
	if (m_sSrc.nIndex >= m_arIndex[m_sSrc.nSkillIndex].Num() - 1)
	{
		m_sSrc.eSkillID = FE_SkillID::E_NONE;
	}
	return true;
}

void UC_SkillMGR::E_SetNextMontage()
{
	m_sSrc.nIndex++;
	if (m_sSrc.nIndex >= m_arIndex[m_sSrc.nSkillIndex].Num())
		m_sSrc.nIndex = 0;
	m_sSrc.nPlayIndex = m_arIndex[m_sSrc.nSkillIndex][m_sSrc.nIndex];
}
