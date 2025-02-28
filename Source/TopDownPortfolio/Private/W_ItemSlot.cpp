#include "W_ItemSlot.h"
#include "A_PlayerController.h"
#include "C_Inventory.h"
#include "BFL_ItemLibrary.h"

UW_ItemSlot::UW_ItemSlot(const FObjectInitializer& ObjectInitializer) : 
	UUserWidget{ ObjectInitializer }, m_pPlayer{}, m_pInventory{}, m_nItemID{}, m_nItemCount{}, m_eItemType {}, m_nIndexY{}, m_nIndexX{}
{
}

void UW_ItemSlot::E_SetItemID(int nItemID, int nItemCount)
{ 
	m_nItemID = nItemID;
	m_nItemCount = nItemCount;
	E_RsetWidget_Implementation();
}

int UW_ItemSlot::E_GetSlotIndex()
{
	return m_nIndexY * m_pInventory->E_GetSlotSizeY() + m_nIndexX;
}

bool UW_ItemSlot::E_Switch(UW_ItemSlot* pDst)
{
	if (!pDst || m_eItemType != pDst->m_eItemType)
		return false;
	uint8 eItemFlag{};
	UBFL_ItemLibrary::E_GetItemFlag(this, m_eItemType, m_nItemID, eItemFlag);
	if (m_nItemID == pDst->m_nItemID && (eItemFlag & (uint8)FE_ItemManageabilityFlag::E_Bundlable))
	{
		pDst->m_nItemCount += m_nItemCount;
		m_nItemID = 0;
		m_nItemCount = 0;
	}
	Swap<int>(m_nItemID, pDst->m_nItemID);
	Swap<int>(m_nItemCount, pDst->m_nItemCount);
	return true;
}

void UW_ItemSlot::NativeOnInitialized()
{
	UUserWidget::NativeOnInitialized();
	m_pPlayer = Cast< AA_PlayerController>(GetOwningPlayer());
	if (m_pPlayer)
	{
		m_pInventory = m_pPlayer->E_GetInventory();
	}
}
