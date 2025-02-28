#include "C_ItemDataTable.h"
#include "Kismet/DataTableFunctionLibrary.h"
#include "D_DataTable.h"

UC_ItemDataTable::UC_ItemDataTable() : 
	UActorComponent{}, m_arDataTable{}, m_mapItemData{}
{
	PrimaryComponentTick.bCanEverTick = false;

	m_mapItemData[(uint8)FE_ItemType::E_NONE].Add({ 0, &m_arDefaultStruct });
	m_mapItemData[(uint8)FE_ItemType::E_ItemSlotMAX].Add({ 0, &m_arDefaultStruct });
	m_mapItemData[(uint8)FE_ItemType::E_Collectibles].Add({ 0, &m_arDefaultStruct_Collectibles });
	m_mapItemData[(uint8)FE_ItemType::E_Money].Add({ 0, &m_arDefaultStruct_Money });
	m_mapItemData[(uint8)FE_ItemType::E_Equipment].Add({ 0, &m_arDefaultStruct_Equip });
	m_mapItemData[(uint8)FE_ItemType::E_Consumable].Add({ 0, &m_arDefaultStruct_Consumable });

	E_SetDataTable(FE_ItemType::E_Collectibles, N_DefaultPath::E_CollectionItemData);
	E_SetDataTable(FE_ItemType::E_Money, N_DefaultPath::E_MoneyData);
	E_SetDataTable(FE_ItemType::E_Equipment, N_DefaultPath::E_EquipItemData);
	E_SetDataTable(FE_ItemType::E_Equipment, N_DefaultPath::E_EquipItemData);
	//E_SetDataTable(FE_ItemType::E_Consumable, N_DefaultPath::E_EquipItemData);
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

void UC_ItemDataTable::E_SetDataTable(FE_ItemType eItemType, uint8 ePathType)
{
	m_arDataTable[(uint8)eItemType] = UD_DataTable::E_GetDefault_DataTable((N_DefaultPath::E_DataTable)ePathType);
}

const FS_ItemData* UC_ItemDataTable::E_GetItemData(FE_ItemType eType, int nItemID)
{
	TMap<int, const FS_ItemData*>* pDataMap = &m_mapItemData[(uint8)eType];
	const FS_ItemData* const* ppData = pDataMap->Find(nItemID);
	if (!ppData)
		ppData = pDataMap->Find(0);
	return *ppData;
}

void UC_ItemDataTable::E_GeItemData()
{
	E_GeItemData(FE_ItemType::E_Equipment);
	E_GeItemData(FE_ItemType::E_Consumable);
	E_GeItemData(FE_ItemType::E_Collectibles);
	E_GeItemData(FE_ItemType::E_Money);
}

FName UC_ItemDataTable::E_GetItemName(FE_ItemType eItemType, int nItemID)
{
	const FS_ItemData* pData = E_GetItemData(eItemType, nItemID);
	return pData->strItemName;
}

uint8 UC_ItemDataTable::E_GetItemFlag(FE_ItemType eItemType, int nItemID)
{
	const FS_ItemData* pData = E_GetItemData(eItemType, nItemID);
	return pData->eItemManageabilityFlag;
}

UTexture2D* UC_ItemDataTable::E_GetItemTexture(FE_ItemType eItemType, int nItemID)
{
	const FS_ItemData* pData = E_GetItemData(eItemType, nItemID);
	return pData->pWidgetTextrue;
}

UStaticMesh* UC_ItemDataTable::E_GetItemStaticMesh(FE_ItemType eItemType, int nItemID)
{
	const FS_ItemData* pData = E_GetItemData(eItemType, nItemID);
	return pData->pItemActorMesh;
}

FName UC_ItemDataTable::E_GetItemDesc(FE_ItemType eItemType, int nItemID)
{
	const FS_ItemData* pData = E_GetItemData(eItemType, nItemID);
	return pData->strItemDesc;
}
