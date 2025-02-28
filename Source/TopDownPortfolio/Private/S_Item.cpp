#include "S_Item.h"

FS_ItemData::FS_ItemData() :
	FTableRowBase{}, nItemID{}, eItemType{}, strItemName{}, eItemManageabilityFlag{}, pWidgetTextrue{}, pItemActorMesh{}, strItemDesc{}
{
	eItemManageabilityFlag = 0b11111111;
}

FS_ItemData_Equipment::FS_ItemData_Equipment() :
	FS_ItemData{}, eEquipmentType{}
{
	eItemType = FE_ItemType::E_Equipment;
	eItemManageabilityFlag ^= (uint8)FE_ItemManageabilityFlag::E_Bundlable;
}

FS_ItemData_Consumable::FS_ItemData_Consumable() :
	FS_ItemData{}, eConsumableType{}
{
	eItemType = FE_ItemType::E_Consumable;
	eItemManageabilityFlag ^= (uint8)FE_ItemManageabilityFlag::E_Dismantlable;
}

FS_ItemData_Collectibles::FS_ItemData_Collectibles() : 
	FS_ItemData{}
{
	eItemType = FE_ItemType::E_Collectibles;
	eItemManageabilityFlag ^= (uint8)FE_ItemManageabilityFlag::E_Dismantlable;
}

FS_ItemData_Money::FS_ItemData_Money() :
	FS_ItemData{}, eMoneyType{}
{
	eItemType = FE_ItemType::E_Money;
	eItemManageabilityFlag = (uint8)FE_ItemManageabilityFlag::E_Sellable;
}

