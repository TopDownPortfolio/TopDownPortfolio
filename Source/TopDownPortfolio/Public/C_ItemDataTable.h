#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "S_Item.h"
#include "C_ItemDataTable.generated.h"

class UDataTable;

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class TOPDOWNPORTFOLIO_API UC_ItemDataTable : public UActorComponent
{
	GENERATED_BODY()
private:
	UDataTable* m_arDataTable[(uint8)FE_ItemType::E_EnumMAX];
	TMap<int, const FS_ItemData*> m_mapItemData[(uint8)FE_ItemType::E_EnumMAX];
	FS_ItemData_Equipment m_arDefaultStruct_Equip;
	FS_ItemData_Consumable m_arDefaultStruct_Consumable;
	FS_ItemData_Collectibles m_arDefaultStruct_Collectibles;
	FS_ItemData_Money m_arDefaultStruct_Money;
	FS_ItemData m_arDefaultStruct;
public:	
	UC_ItemDataTable();

protected:
	virtual void BeginPlay() override;

private:
	void E_GetDataTable(FE_ItemType eType);
	void E_SetDataTable(FE_ItemType eItemType, uint8 ePathType);
	const FS_ItemData* E_GetItemData(FE_ItemType eType, int nItemID);
	UTexture2D* E_LoadSynchronousTexture(TSoftObjectPtr<UTexture2D> pSoftObject);
	UStaticMesh* E_LoadSynchronousMesh(TSoftObjectPtr<UStaticMesh> pSoftObject);
public:	
	FName E_GetItemName(FE_ItemType eItemType, int nItemID);
	uint8 E_GetItemFlag(FE_ItemType eItemType, int nItemID);
	UTexture2D* E_GetItemTexture(FE_ItemType eItemType, int nItemID);
	UStaticMesh* E_GetItemStaticMesh(FE_ItemType eItemType, int nItemID);
	FName E_GetItemDesc(FE_ItemType eItemType, int nItemID);
};
