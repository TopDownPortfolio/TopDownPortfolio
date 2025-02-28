#include "C_Inventory.h"
#include "W_ItemSlot.h"
#include "BFL_ItemLibrary.h"

UC_Inventory::UC_Inventory() :
	UActorComponent{}, m_arItemSlot{}, m_arMoneySlot{}, m_arInventorySlot {}, m_mapItem{}
{
	using namespace std;
	PrimaryComponentTick.bCanEverTick = false;
	m_arItemSlot[0].resize(1, vector<S_ItemSlot>(1));
	m_arInventorySlot[0] = &m_arItemSlot[0];
	m_arInventorySlot[(uint8)FE_ItemType::E_ItemSlotMAX] = &m_arItemSlot[0];

	for (uint8 k = 1; k < (uint8)FE_ItemType::E_ItemSlotMAX; k++)
	{
		m_arItemSlot[k].resize(E_ArSize::E_ItemSlotY, vector<S_ItemSlot>(E_ArSize::E_ItemSlotX));
		m_arInventorySlot[k] = &m_arItemSlot[k];
	}
	m_arMoneySlot.resize(1, vector<S_ItemSlot>((uint8)FE_MoneyType::E_EnumMAX));
	m_arInventorySlot[(uint8)FE_ItemType::E_Money] = &m_arMoneySlot;

	for (uint8 k = 1; k < (uint8)FE_ItemType::E_ItemSlotMAX; k++)
	{
		for (int i = 0; i < E_ArSize::E_ItemSlotY; i++)
		{
			for (int j = 0; j < E_ArSize::E_ItemSlotX; j++)
			{
				S_ItemSlot* pSlot = E_GetInventroySlot((FE_ItemType)k, i, j);
				pSlot->sInstanceData.eItemType = (FE_ItemType)k;
				pSlot->nIndexY = i;
				pSlot->nIndexX = j;
			}
		}
	}
}

void UC_Inventory::BeginPlay()
{
	UActorComponent::BeginPlay();
}

UC_Inventory::S_ItemSlot* UC_Inventory::E_GetEmpthySlot(FE_ItemType eItemType)
{
	S_ItemSlot* pResult{};
	for (int i = 0; i < E_ArSize::E_ItemSlotY && pResult == nullptr; i++)
	{
		for (int j = 0; j < E_ArSize::E_ItemSlotX && pResult == nullptr; j++)
		{
			S_ItemSlot* pSlot = E_GetInventroySlot(eItemType, i, j);
			if (pSlot->sInstanceData.nItemID == 0)
				pResult = pSlot;
		}
	}
	return pResult;
}

UC_Inventory::S_ItemSlot* UC_Inventory::E_GetInventroySlot(FE_ItemType eItemType, int nIndexY, int nIndexX)
{
	using namespace std;
	S_ItemSlot* pReusult{};
	vector<vector<S_ItemSlot>>* arSlot = m_arInventorySlot[(uint8)eItemType];
	if (arSlot->size() > nIndexY && (*arSlot)[0].size() > nIndexX)
	{
		pReusult = &(*arSlot)[nIndexY][nIndexX];
	}
	if (!pReusult)
		pReusult = &(*arSlot)[0][0];
	return  pReusult;
}

int UC_Inventory::E_GetItemCounts(FE_ItemType eItemType, int nIndexY, int nIndexX)
{
	return E_GetInventroySlot(eItemType, nIndexY, nIndexX)->sInstanceData.nItemCount;
}

int UC_Inventory::E_GetItemID(FE_ItemType eItemType, int nIndexY, int nIndexX)
{
	return E_GetInventroySlot(eItemType, nIndexY, nIndexX)->sInstanceData.nItemID;
}

bool UC_Inventory::E_PushItem(FS_ItemInstanceData* sInstanceData)
{
	int nItemID = sInstanceData->nItemID;
	int nCount = sInstanceData->nItemCount;
	uint8 nType = (uint8)sInstanceData->eItemType;
	S_ItemSlot*& pSlot = m_mapItem[nType].FindOrAdd(nItemID);
	uint8 eItemFlag{};
	UBFL_ItemLibrary::E_GetItemFlag(this, sInstanceData->eItemType, nItemID, eItemFlag);
	if (!pSlot || !(eItemFlag & (uint8)FE_ItemManageabilityFlag::E_Bundlable))
		pSlot = E_GetEmpthySlot(sInstanceData->eItemType);
	if (!pSlot)
		return false;
	pSlot->sInstanceData.nItemID = nItemID;
	pSlot->sInstanceData.nItemCount += nCount;
	if (pSlot->pWidget)
		pSlot->pWidget->E_SetItemID(pSlot->sInstanceData.nItemID, pSlot->sInstanceData.nItemCount);
	return true;
}

bool UC_Inventory::E_PopItem(FS_ItemInstanceData* sInstanceData, int& nRemainCount)
{
	int nItemID = sInstanceData->nItemID;
	int nCount = sInstanceData->nItemCount;
	uint8 nType = (uint8)sInstanceData->eItemType;
	S_ItemSlot*& pSlot = m_mapItem[nType].FindOrAdd(nItemID);
	if (!pSlot)
		return false;
	bool bResult{};
	if (pSlot->sInstanceData.nItemCount >= nCount)
	{
		bResult = true;
		pSlot->sInstanceData.nItemCount -= nCount;
		nRemainCount = pSlot->sInstanceData.nItemCount;
		if (pSlot->sInstanceData.nItemCount <= 0)
			pSlot->sInstanceData.nItemID = 0;
	}
	return bResult;
}

bool UC_Inventory::E_PushItem(FS_ItemInstanceData sInstanceData)
{
	return E_PushItem(&sInstanceData);
}

bool UC_Inventory::E_PopItem(FS_ItemInstanceData sInstanceData, int& nRemainCount)
{
	return E_PopItem(&sInstanceData, nRemainCount);
}

void UC_Inventory::E_SetItemSlotWidget(FE_ItemType eItemType,int nIndexY, int nIndexX, UW_ItemSlot* pWidget)
{
	E_GetInventroySlot(eItemType, nIndexY, nIndexX)->pWidget = pWidget;
}

bool UC_Inventory::E_Switch(UW_ItemSlot* pSrc, UW_ItemSlot* pDst)
{
	if (!pSrc || pSrc == pDst)
		return false;
	if (pSrc->E_Switch(pDst) == false)
		return false;
	pSrc->E_RsetWidget_Implementation();
	pDst->E_RsetWidget_Implementation();

	m_mapItem[(uint8)pSrc->m_eItemType];
	return true;
}
