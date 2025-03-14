#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "S_Item.h"
#include "W_ItemSlot.generated.h"

class UC_Inventory;
class AA_PlayerController;

UCLASS()
class TOPDOWNPORTFOLIO_API UW_ItemSlot : public UUserWidget
{
	GENERATED_BODY()
protected:
	UPROPERTY(BlueprintReadOnly, VisibleAnywhere, Category = "Item", meta = (AllowPrivateAccess = "true"))
	AA_PlayerController* m_pPlayer;
	UPROPERTY(BlueprintReadOnly, VisibleAnywhere, Category = "Item", meta = (AllowPrivateAccess = "true"))
	UC_Inventory* m_pInventory;
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Item", meta = (AllowPrivateAccess = "true"))
	FS_ItemInstanceData m_sItemInstanceData;
	UPROPERTY(BlueprintReadOnly, EditInstanceOnly, Category = "Item", meta = (ClampMin = "0", AllowPrivateAccess = "true"))
	int m_nIndexY;
	UPROPERTY(BlueprintReadOnly, EditInstanceOnly, Category = "Item", meta = (ClampMin = "0", AllowPrivateAccess = "true"))
	int m_nIndexX;
public:
	UW_ItemSlot(const FObjectInitializer& ObjectInitializer);

	FE_ItemType E_GetItemType() { return m_sItemInstanceData.eItemType; }
	int E_GetItemID() { return m_sItemInstanceData.nItemID; }
	int E_GetSlotIndexX() { return m_nIndexX; }
	int E_GetSlotIndexY() { return m_nIndexY; }
	void E_UpdateItem();
	UFUNCTION(BlueprintPure)
	int E_GetSlotIndex();
	UFUNCTION(BlueprintImplementableEvent)
	void E_RsetWidget();
	void E_InitItemSlot(FE_ItemType eItemType, int nIndexY, int nIndexX);
protected:
	virtual void NativeOnInitialized() override;
	void E_RsetWidget_Implementation() {}
};
