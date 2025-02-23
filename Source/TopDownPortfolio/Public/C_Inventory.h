#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "C_Inventory.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class TOPDOWNPORTFOLIO_API UC_Inventory : public UActorComponent
{
	GENERATED_BODY()
private:
	enum E_InventorySize
	{
		E_SIZEY = 10,
		E_SIZEX = 10,
	};
	struct S_ItemSlot
	{
		int nItemID;
		int nIndexY;
		int nIndexX;
		int nItemCount;
	};

	S_ItemSlot m_arItemSlot[E_InventorySize::E_SIZEY][E_InventorySize::E_SIZEX];
	TMap<int, S_ItemSlot*> m_mapItem;
public:	
	UC_Inventory();
protected:
	virtual void BeginPlay() override;

	S_ItemSlot* E_GetEmpthySlot();
	S_ItemSlot* E_GetSlot(int nIndexY, int nIndexX);
public:	
	UFUNCTION(BlueprintPure)
	int E_GetItemCounts(int nIndexY, int nIndexX);
	UFUNCTION(BlueprintPure)
	int E_GetItemID(int nIndexY, int nIndexX);
	bool E_PushItem(int nItemID, int nCount);
	bool E_PopItem(int nItemID, int nCount, int& nRemainCount);
};
