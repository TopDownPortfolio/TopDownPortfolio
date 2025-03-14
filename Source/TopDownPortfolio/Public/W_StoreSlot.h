#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "S_Item.h"
#include "W_StoreSlot.generated.h"

class UScrollBoxSlot;
class APlayerController;
class UC_Inventory;
class UButton;

UCLASS()
class TOPDOWNPORTFOLIO_API UW_StoreSlot : public UUserWidget
{
	GENERATED_BODY()
protected:
	UPROPERTY(BlueprintReadOnly, EditInstanceOnly, Category = "Store", meta = (ExposeOnSpawn = "TRUE", AllowPrivateAccess = "true"))
	FS_ItemStoreData m_sData;
	UPROPERTY(BlueprintReadOnly, VisibleAnywhere, Category = "Store", meta = (AllowPrivateAccess = "true"))
	UC_Inventory* m_pInventory;
	UPROPERTY(BlueprintReadOnly, Category = "Store", meta = ( AllowPrivateAccess = "true"))
	FLinearColor m_sRetailColor;
	UPROPERTY(BlueprintReadOnly,VisibleAnywhere, Category = "Store", meta = ( AllowPrivateAccess = "true"))
	int m_nRetailCount;
public:
	UPROPERTY(BlueprintReadWrite, meta = (BindWidget))
	UButton* pSellingButton;
	UW_StoreSlot(const FObjectInitializer& ObjectInitializer);

protected:
	UFUNCTION(BlueprintCallable, meta = (AllowPrivateAccess = "true"))
	void E_UpdateSlot();
	virtual void NativeOnInitialized() override;
	virtual void NativeConstruct() override; 
	FText E_GetItemName(const FS_ItemInstanceData& sData);
	FSlateBrush E_GetBrush(const FS_ItemInstanceData& sData);
	UFUNCTION()
	void E_SellingButtonRelease();
public:
	void E_SetStoreData(FS_ItemStoreData& sSrcData);

	void E_SetInventory(APlayerController* pPlayer);

	UFUNCTION(BlueprintCallable)
	bool E_SellingItem();


	UFUNCTION(BlueprintPure)
	FText E_GetSellingName();
	UFUNCTION(BlueprintPure)
	FText E_GetRetailName();
	UFUNCTION(BlueprintPure)
	FSlateBrush E_GetSellingBrush();
	UFUNCTION(BlueprintPure)
	FSlateBrush E_GetRetailBrush();
};
