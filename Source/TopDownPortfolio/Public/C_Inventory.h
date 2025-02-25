#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "S_Item.h"
#include <vector>
#include "C_Inventory.generated.h"

class UUserWidget;
class UW_ItemSlot;

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class TOPDOWNPORTFOLIO_API UC_Inventory : public UActorComponent
{
	GENERATED_BODY()
private:
	enum E_ArSize
	{
		E_ItemSlotX = 10,
		E_ItemSlotY = 10,
	};

	struct S_ItemSlot
	{
		FS_ItemInstanceData sInstanceData;
		int nIndexY;
		int nIndexX;
		UW_ItemSlot* pWidget;
	};
	std::vector<std::vector<S_ItemSlot>> m_arItemSlot[(uint8)FE_ItemType::E_ItemSlotMAX];
	std::vector<std::vector<S_ItemSlot>> m_arMoneySlot;
	std::vector<std::vector<S_ItemSlot>>* m_arInventorySlot[(uint8)FE_ItemType::E_EnumMAX];
	TMap<int, S_ItemSlot*> m_mapItem[(uint8)FE_ItemType::E_EnumMAX];
public:	
	UC_Inventory();
protected:
	virtual void BeginPlay() override;

	S_ItemSlot* E_GetEmpthySlot(FE_ItemType eItemType);
	S_ItemSlot* E_GetInventroySlot(FE_ItemType eItemType, int nIndexY, int nIndexX = 0);
public:	
	UFUNCTION(BlueprintPure)
	int E_GetSlotSizeX() { return E_ArSize::E_ItemSlotX; }
	UFUNCTION(BlueprintPure)
	int E_GetSlotSizeY() { return E_ArSize::E_ItemSlotY; }
	UFUNCTION(BlueprintPure)
	int E_GetItemCounts(FE_ItemType eItemType, int nIndexY, int nIndexX);
	UFUNCTION(BlueprintPure)
	int E_GetItemID(FE_ItemType eItemType, int nIndexY, int nIndexX);

	bool E_PushItem(FS_ItemInstanceData* sInstanceData);
	bool E_PopItem(FS_ItemInstanceData* sInstanceData, int& nRemainCount);

	UFUNCTION(BlueprintCallable)
	bool E_PushItem(FS_ItemInstanceData sInstanceData);
	UFUNCTION(BlueprintCallable)
	bool E_PopItem(FS_ItemInstanceData sInstanceData, int& nRemainCount);
	UFUNCTION(BlueprintCallable)
	void E_SetItemSlotWidget(FE_ItemType eItemType, int nIndexY, int nIndexX, UW_ItemSlot* pWidget);

	UFUNCTION(BlueprintCallable)
	bool E_Switch(UW_ItemSlot* pSrc, UW_ItemSlot* pDst);
};
