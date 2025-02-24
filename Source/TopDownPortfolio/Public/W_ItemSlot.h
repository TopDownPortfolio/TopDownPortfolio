#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "W_ItemSlot.generated.h"

class UC_Inventory;
class AA_PlayerController;

UCLASS()
class TOPDOWNPORTFOLIO_API UW_ItemSlot : public UUserWidget
{
	GENERATED_BODY()

public:
	UPROPERTY(BlueprintReadOnly, VisibleAnywhere, Category = "Item", meta = (ClampMin = "0"))
	AA_PlayerController* m_pPlayer;
	UPROPERTY(BlueprintReadOnly, VisibleAnywhere, Category = "Item", meta = (ClampMin = "0"))
	UC_Inventory* m_pInventory;
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Item", meta = (ClampMin = "0"))
	int m_nItemID;
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Item", meta = (ClampMin = "0", ExposeOnSpawn = "TRUE"))
	int m_nIndexY;
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Item", meta = (ClampMin = "0", ExposeOnSpawn = "TRUE"))
	int m_nIndexX;
public:
	UW_ItemSlot(const FObjectInitializer& ObjectInitializer);

	void E_SetItemID(int nItemID);

	UFUNCTION(BlueprintImplementableEvent)
	void E_RsetWidget();
	void E_RsetWidget_Implementation() {}
	protected:
		virtual void NativeOnInitialized() override;
};
