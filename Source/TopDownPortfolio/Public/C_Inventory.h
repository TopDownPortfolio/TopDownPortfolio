#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "S_Item.h"
#include <vector>
#include <list>
#include "Components/UniformGridPanel.h"
#include "C_Inventory.generated.h"

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
	//TMap<int, std::list<S_ItemSlot*>> m_mapItem[(uint8)FE_ItemType::E_EnumMAX];
	S_ItemSlot m_pDummySlot;
public:	
	UC_Inventory();
protected:
	virtual void BeginPlay() override;

	S_ItemSlot* E_GetSameItemIDSlot(FE_ItemType eItemType, int nItemID= 0);
	S_ItemSlot* E_GetInventroySlot(FE_ItemType eItemType,int nIndexY, int nIndexX = 0);
	void E_MergeSlot(S_ItemSlot* pSrc, S_ItemSlot* pDst);
	void E_SetDummy(FE_ItemType eItemType, int nItemID = 0, int nItemCount = 0);
	void E_SwitchSlot(S_ItemSlot* pSrc, S_ItemSlot* pDst);
	void E_UpdateSlot(S_ItemSlot* pSlot);
	void E_GetSameSlots(FE_ItemType eItemType, int nItemID, std::vector<S_ItemSlot*>& arSlots, int& nCounts);
public:	
	UFUNCTION(BlueprintPure)
	int E_GetItemTotalCount(const FS_ItemInstanceData& sInstanceData);
	void E_GetItemTotalCount(FE_ItemType eItemType, int nItemID, int& nCounts);
	UFUNCTION(BlueprintPure)
	int E_GetSlotSizeX() { return E_ArSize::E_ItemSlotX; }
	UFUNCTION(BlueprintPure)
	int E_GetSlotSizeY() { return E_ArSize::E_ItemSlotY; }

	UFUNCTION(BlueprintPure)
	int E_GetItemCounts(FE_ItemType eItemType, int nIndexY, int nIndexX);
	UFUNCTION(BlueprintPure)
	int E_GetItemID(FE_ItemType eItemType, int nIndexY, int nIndexX);


	UFUNCTION(BlueprintCallable)
	bool E_PushItem(FS_ItemInstanceData sInstanceData);
	bool E_PushItem(FS_ItemInstanceData* sInstanceData);


	UFUNCTION(BlueprintCallable)
	bool E_PopItem(FS_ItemInstanceData sInstanceData, int& nRemainCount);
	bool E_PopItem(FS_ItemInstanceData* sInstanceData, int& nRemainCount);
	UFUNCTION(BlueprintCallable)
	bool E_RemoveItem(UW_ItemSlot* pWidget);

	UFUNCTION(BlueprintCallable)
	bool E_Switch(UW_ItemSlot* pSrc, UW_ItemSlot* pDst);
	UFUNCTION(BlueprintCallable)
	void E_CreateInventoryWidget(UUniformGridPanel* pGridPanel, FE_ItemType eItemType, TSubclassOf< UW_ItemSlot> wSlot);
	UFUNCTION(BlueprintCallable)
	void E_SetMoneySlot(UUniformGridPanel* pGridPanel);
};
