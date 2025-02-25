#include "C_ItemDataTable.h"
#include "Kismet/DataTableFunctionLibrary.h"
#include "D_DataTable.h"

UC_ItemDataTable::UC_ItemDataTable() : 
	UActorComponent{}, m_arDataTable{}, m_mapItemData{}
{
	PrimaryComponentTick.bCanEverTick = false;
	m_arDataTable[(uint8)FE_ItemType::E_Collectibles] = UD_DataTable::E_GetDefault_DataTable(N_DefaultPath::E_CollectionItemData);
}

void UC_ItemDataTable::BeginPlay()
{
	UActorComponent::BeginPlay();
	E_GeItemData();
}

void UC_ItemDataTable::E_GeItemData(FE_ItemType eType)
{
	uint8 nType = (uint8)eType;
	UDataTable* pDataTable = m_arDataTable[nType];
	if (!pDataTable)
		return;
	TArray< FS_ItemData*> arData{};
	TMap<int, const FS_ItemData*>* pDataMap = &m_mapItemData[nType];
	pDataTable->GetAllRows("", arData);
	for (FS_ItemData*& pData : arData)
	{
		pDataMap->Add({ pData->nItemID, pData });
	}
}

const FS_ItemData* UC_ItemDataTable::E_GetItemData(FE_ItemType eType, int nItemID)
{
	TMap<int, const FS_ItemData*>* pDataMap = &m_mapItemData[(uint8)eType];
	const FS_ItemData* const* ppData = pDataMap->Find(nItemID);
	if (!ppData)
		return nullptr;
	return *ppData;
}

void UC_ItemDataTable::E_GeItemData()
{
	E_GeItemData(FE_ItemType::E_Collectibles);
}

FName UC_ItemDataTable::E_GetItemName(FE_ItemType eItemType, int nItemID)
{
	const FS_ItemData* pData = E_GetItemData(eItemType, nItemID);
	if (pData)
		return pData->strItemName;
	return FName();
}

uint8 UC_ItemDataTable::E_GetItemFlag(FE_ItemType eItemType, int nItemID)
{
	const FS_ItemData* pData = E_GetItemData(eItemType, nItemID);
	if (pData)
		return pData->eItemManageabilityFlag;
	return uint8();
}

UTexture2D* UC_ItemDataTable::E_GetItemTexture(FE_ItemType eItemType, int nItemID)
{
	const FS_ItemData* pData = E_GetItemData(eItemType, nItemID);
	if (pData)
		return pData->pWidgetTextrue;
	return nullptr;
}

UStaticMesh* UC_ItemDataTable::E_GetItemStaticMesh(FE_ItemType eItemType, int nItemID)
{
	const FS_ItemData* pData = E_GetItemData(eItemType, nItemID);
	if (pData)
		return pData->pItemActorMesh;
	return nullptr;
}

FName UC_ItemDataTable::E_GetItemDesc(FE_ItemType eItemType, int nItemID)
{
	const FS_ItemData* pData = E_GetItemData(eItemType, nItemID);
	if (pData)
		return pData->strItemDesc;
	return FName();
}
