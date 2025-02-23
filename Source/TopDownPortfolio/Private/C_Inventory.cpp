#include "C_Inventory.h"

UC_Inventory::UC_Inventory()
{
	PrimaryComponentTick.bCanEverTick = false;
	for (int i = 0; i < E_InventorySize::E_SIZEY; i++)
	{
		for (int j = 0; j < E_InventorySize::E_SIZEX; j++)
		{
			S_ItemSlot* pSlot = E_GetSlot(i, j);
			pSlot->nIndexY = i;
			pSlot->nIndexX = j;
		}
	}
}

void UC_Inventory::BeginPlay()
{
	Super::BeginPlay();
}

UC_Inventory::S_ItemSlot* UC_Inventory::E_GetEmpthySlot()
{
	S_ItemSlot* pResult{};
	for (int i = 0; i < E_InventorySize::E_SIZEY && pResult == nullptr; i++)
	{
		for (int j = 0; j < E_InventorySize::E_SIZEX && pResult == nullptr; j++)
		{
			S_ItemSlot* pSlot = E_GetSlot(i, j);
			if (pSlot->nItemID == 0)
				pResult = pSlot;
		}
	}
	return pResult;
}

UC_Inventory::S_ItemSlot* UC_Inventory::E_GetSlot(int nIndexY, int nIndexX)
{
	return &m_arItemSlot[nIndexY][nIndexX];
}

int UC_Inventory::E_GetItemCounts(int nIndexY, int nIndexX)
{
	return E_GetSlot(nIndexY , nIndexX)->nItemCount;
}

int UC_Inventory::E_GetItemID(int nIndexY, int nIndexX)
{
	return E_GetSlot(nIndexY, nIndexX)->nItemID;
}

bool UC_Inventory::E_PushItem(int nItemID, int nCount)
{
	S_ItemSlot*& pSlot = m_mapItem.FindOrAdd(nItemID);
	if (!pSlot)
		pSlot = E_GetEmpthySlot();
	if (!pSlot)
		return false;
	pSlot->nItemID = nItemID;
	pSlot->nItemCount += nCount;
	return true;
}

bool UC_Inventory::E_PopItem(int nItemID, int nCount, int& nRemainCount)
{
	S_ItemSlot*& pSlot = m_mapItem.FindOrAdd(nItemID);
	if (!pSlot)
		return false;
	bool bResult{};
	if (pSlot->nItemCount >= nCount)
	{
		bResult = true;
		pSlot->nItemCount -= nCount;
		nRemainCount = pSlot->nItemCount;
		if (pSlot->nItemCount <= 0)
			pSlot->nItemID = 0;
	}
	return bResult;
}
