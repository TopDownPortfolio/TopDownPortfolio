#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "E_Item.h"
#include "W_ItemSlot.generated.h"

class UC_Inventory;
class AA_PlayerController;

UCLASS()
class TOPDOWNPORTFOLIO_API UW_ItemSlot : public UUserWidget
{
	GENERATED_BODY()

public:
	UPROPERTY(BlueprintReadOnly, VisibleAnywhere, Category = "Item")
	AA_PlayerController* m_pPlayer;
	UPROPERTY(BlueprintReadOnly, VisibleAnywhere, Category = "Item")
	UC_Inventory* m_pInventory;
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Item", meta = (ClampMin = "0"))
	int m_nItemID;
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Item")
	int m_nItemCount;
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Item", meta = (ExposeOnSpawn = "TRUE"))
	FE_ItemType m_eItemType;
	UPROPERTY(BlueprintReadOnly, EditAnywhere, Category = "Item", meta = (ClampMin = "0", ExposeOnSpawn = "TRUE"))
	int m_nIndexY;
	UPROPERTY(BlueprintReadOnly, EditAnywhere, Category = "Item", meta = (ClampMin = "0", ExposeOnSpawn = "TRUE"))
	int m_nIndexX;
public:
	UW_ItemSlot(const FObjectInitializer& ObjectInitializer);

	void E_SetItemID(int nItemID, int nItemCount);
	UFUNCTION(BlueprintPure)
	int E_GetSlotIndex();
	UFUNCTION(BlueprintImplementableEvent)
	void E_RsetWidget();
	void E_RsetWidget_Implementation() {}
	bool E_Switch(UW_ItemSlot* pDst);
protected:
	virtual void NativeOnInitialized() override;

private:
};
