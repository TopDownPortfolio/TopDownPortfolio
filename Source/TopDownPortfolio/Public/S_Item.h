#pragma once

#include "CoreMinimal.h"
#include "Engine/UserDefinedStruct.h"
#include "E_Item.h"
#include "S_Item.generated.h"

USTRUCT(BlueprintType)
struct FS_ItemIDData : public FTableRowBase
{
	GENERATED_USTRUCT_BODY()
public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (ClampMin = "0"))
	int nItemID;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FE_ItemType eItemType;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	UTexture2D* pWidgetTextrue;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	UStaticMesh* pItemActorMesh;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FName strItemName;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FName strItemDesc;
};

USTRUCT(BlueprintType)
struct FS_ItemData : public FTableRowBase
{
	GENERATED_USTRUCT_BODY()
public:
	FS_ItemData() = default;
	virtual ~FS_ItemData() = default;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "1_ItemData", meta = (ClampMin = "0"))
	int nItemID;
	UPROPERTY(EditAnyWhere, BlueprintReadWrite, Category = "1_ItemData", meta = (Bitmask, BitmaskEnum = FE_ItemManageabilityFlag))
	uint8 eItemManageabilityFlag = 0b00000111;
};

USTRUCT()
struct FS_ItemData_Equipment : public FS_ItemData
{
	GENERATED_USTRUCT_BODY()
public:
	//FS_ItemData_Equipment();
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "2_Equipment")
	FE_EquipmentType eEquipmentType;
};

USTRUCT()
struct FS_ItemData_Consumable : public FS_ItemData
{
	GENERATED_USTRUCT_BODY()
public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "2_Consumable")
	FE_ConsumableType eConsumableType;
}; 

USTRUCT()
struct FS_ItemData_Collectibles : public FS_ItemData
{
	GENERATED_USTRUCT_BODY()
public:
};

