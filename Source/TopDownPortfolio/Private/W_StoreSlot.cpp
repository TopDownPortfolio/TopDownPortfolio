#include "W_StoreSlot.h"
#include "A_PlayerController.h"
#include "C_Inventory.h"
#include "Components/Button.h"
#include "BFL_ItemLibrary.h"

UW_StoreSlot::UW_StoreSlot(const FObjectInitializer& ObjectInitializer) :
	UUserWidget{ ObjectInitializer }, m_sData{}, m_pInventory{}, m_sRetailColor{}, m_nRetailCount{}, pSellingButton {}
{
	m_sRetailColor = FLinearColor::White;
}
void UW_StoreSlot::E_UpdateSlot()
{
	m_sRetailColor.G = 0.0f;
	m_sRetailColor.B = 0.0f;
	pSellingButton->SetVisibility(ESlateVisibility::HitTestInvisible);
		pSellingButton->bIsEnabled = true;
	if (m_nRetailCount >= m_sData.sRetailItem.nItemCount)
	{
		m_sRetailColor.G = 1.0f;
		m_sRetailColor.B = 1.0f;
		pSellingButton->SetVisibility(ESlateVisibility::Visible);
		pSellingButton->bIsEnabled = false;
	}
}

void UW_StoreSlot::NativeOnInitialized()
{
	UUserWidget::NativeOnInitialized();
	if (pSellingButton)
		pSellingButton->OnReleased.AddDynamic(this, &UW_StoreSlot::E_SellingButtonRelease);
}

void UW_StoreSlot::NativeConstruct()
{
	UUserWidget::NativeConstruct();
	if (!m_pInventory)
		return;
	m_nRetailCount = m_pInventory->E_GetItemTotalCount(m_sData.sRetailItem);
	E_UpdateSlot();
}

FText UW_StoreSlot::E_GetItemName(const FS_ItemInstanceData& sData)
{
	FName ItemName{};
	UBFL_ItemLibrary::E_GetItemName(this, sData.eItemType, sData.nItemID, ItemName);
	return FText::FromName(ItemName);
}

FSlateBrush UW_StoreSlot::E_GetBrush(const FS_ItemInstanceData& sData)
{
	FSlateBrush ItemImage{};
	ItemImage.DrawAs = ESlateBrushDrawType::Image;
	UTexture2D* pTexture{};
	UBFL_ItemLibrary::E_GetItemTexture(this, sData.eItemType, sData.nItemID, pTexture);
	ItemImage.SetResourceObject(pTexture);
	return ItemImage;
}

void UW_StoreSlot::E_SellingButtonRelease()
{
	if (!pSellingButton->IsHovered())
		return;
	E_SellingItem();
}

void UW_StoreSlot::E_SetStoreData(FS_ItemStoreData& sSrcData)
{
	m_sData.sSellingItem = sSrcData.sSellingItem;
	m_sData.nSellableCount= sSrcData.nSellableCount;
	m_sData.sRetailItem = sSrcData.sRetailItem;
}

void UW_StoreSlot::E_SetInventory(APlayerController* pPlayer)
{
	m_pInventory = Cast<AA_PlayerController>(pPlayer)->E_GetInventory();
}

bool UW_StoreSlot::E_SellingItem()
{
	if (!m_pInventory)
		return false;
	m_pInventory->E_PopItem(m_sData.sRetailItem, m_nRetailCount);
	m_pInventory->E_PushItem(m_sData.sSellingItem);
	E_UpdateSlot();
	return true;
}

FText UW_StoreSlot::E_GetSellingName()
{
	return E_GetItemName(m_sData.sSellingItem);
}

FText UW_StoreSlot::E_GetRetailName()
{
	return E_GetItemName(m_sData.sRetailItem);
	
}

FSlateBrush UW_StoreSlot::E_GetSellingBrush()
{
	return E_GetBrush(m_sData.sSellingItem);
}

FSlateBrush UW_StoreSlot::E_GetRetailBrush()
{
	return E_GetBrush(m_sData.sRetailItem);
}
