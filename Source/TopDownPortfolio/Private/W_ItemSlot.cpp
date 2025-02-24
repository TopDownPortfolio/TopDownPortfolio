#include "W_ItemSlot.h"
#include "A_PlayerController.h"
#include "C_Inventory.h"

UW_ItemSlot::UW_ItemSlot(const FObjectInitializer& ObjectInitializer) : 
	UUserWidget{ ObjectInitializer }, m_pPlayer{}, m_pInventory {}, m_nItemID{}, m_nIndexY{}, m_nIndexX{}
{
}

void UW_ItemSlot::E_SetItemID(int nItemID)
{ 
	m_nItemID = nItemID;
	E_RsetWidget_Implementation();
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
