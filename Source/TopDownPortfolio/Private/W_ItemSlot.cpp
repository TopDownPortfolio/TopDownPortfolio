#include "W_ItemSlot.h"
#include "A_PlayerController.h"
#include "C_Inventory.h"
#include "BFL_ItemLibrary.h"

UW_ItemSlot::UW_ItemSlot(const FObjectInitializer& ObjectInitializer) : 
	UUserWidget{ ObjectInitializer }, m_pPlayer{}, m_pInventory{}, m_sItemInstanceData{}, m_nIndexY {}, m_nIndexX{}
{
}

void UW_ItemSlot::E_UpdateItem()
{
	if (!m_pInventory)
		return;
	FE_ItemType eItemType = m_sItemInstanceData.eItemType;
	m_sItemInstanceData.nItemID = m_pInventory->E_GetItemID(eItemType, m_nIndexY, m_nIndexX);
	m_sItemInstanceData.nItemCount = m_pInventory->E_GetItemCounts(eItemType, m_nIndexY, m_nIndexX);
	E_RsetWidget_Implementation();
}

int UW_ItemSlot::E_GetSlotIndex()
{
	return m_nIndexY * m_pInventory->E_GetSlotSizeY() + m_nIndexX;
}


void UW_ItemSlot::E_InitItemSlot(FE_ItemType eItemType, int nIndexY, int nIndexX)
{
	m_sItemInstanceData.eItemType = eItemType;
	m_nIndexY = nIndexY;
	m_nIndexX = nIndexX;
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
