#include "C_AIActionMGR.h"
#include "A_Character_Base.h" 
#include "C_MontageMGR.h"


UC_AIActionMGR::UC_AIActionMGR()
{
	PrimaryComponentTick.bCanEverTick = false;
	//m_pq.((uint8)E_ActionIndex::E_EnumMax);
}

void UC_AIActionMGR::BeginPlay()
{
	UActorComponent::BeginPlay();
	m_pOwner = Cast< AA_Character_Base>(GetOwner());
	if (!m_pOwner)
	{
		DestroyComponent();
		return;
	}
	if (m_pDataTable)
	{
		TArray< FS_AIActionData*> arData{};
		m_pDataTable->GetAllRows< FS_AIActionData>("", arData);
		for (FS_AIActionData*& pData : arData)
		{
			m_mapActionData.Add(pData->nActionIndex, pData);
		}
	}
}

FS_AIActionData* UC_AIActionMGR::E_Pop()
{
	FS_AIActionData* sResult{};
	if (!m_pq.empty())
	{
		sResult = m_pq.top();
		m_pq.pop();
	}
	return sResult;
}

int32 UC_AIActionMGR::E_Push(FS_AIActionData*  pSrc)
{
	int32 nResult = (uint8)E_ActionIndex::E_EnumMax;
	if (m_pq.size() + 1 < (uint8)E_ActionIndex::E_EnumMax)
	{
		nResult = m_pq.size();
		m_pq.push(pSrc);
	}
	return nResult;
}

bool UC_AIActionMGR::E_RegiserAction(int nIndex)
{
	 FS_AIActionData** ppDst = m_mapActionData.Find(nIndex);
	if (!ppDst)
		return false;

	int32 nPushIndex = E_Push(*ppDst);
	FS_AIActionData* pSrc{};
	if (nPushIndex >= (uint8)E_ActionIndex::E_EnumMax)
		pSrc = E_Pop();
	return pSrc != *ppDst;
}

void UC_AIActionMGR::E_PlayAction()
{
	FS_AIActionData* pSrc = E_Pop();
	if (!pSrc)
		return;
	UC_MontageMGR* pMontageMGR = m_pOwner->E_GetMontageMGR();
	bool bResult = pMontageMGR && pMontageMGR->E_CheckPlayable(FE_MontageID::E_01, pSrc->nActionID);
	if (bResult)
	{
		pMontageMGR->E_SetMontageData(FE_MontageID::E_01, pSrc->nActionID);
		pMontageMGR->E_PlayMontage();
	}
	if (!bResult)
	{
		E_Push(pSrc);
	}
}
