#pragma once

#include "CoreMinimal.h"

UENUM(BlueprintType)
enum class FE_ItemType : uint8
{
	E_NONE UMETA(Hidden),
	E_Equipment,
	E_Consumable,
	E_Collectibles,
	E_ItemSlotMAX  UMETA(Hidden),
	E_Money,
	E_EnumMAX  UMETA(Hidden),
};

UENUM(BlueprintType)
enum class FE_MoneyType : uint8
{
	E_NONE UMETA(Hidden),
	E_Gold,
	E_Sling,
	E_EnumMAX  UMETA(Hidden),
};

UENUM(BlueprintType, meta = (Bitflags, UseEnumValuesAsMaskValuesInEditor = "true"))
enum class FE_ItemManageabilityFlag: uint8
{
	E_None				= (0x0) UMETA(Hidden),
	E_Sellable			= (1 << 0),
	E_Dismantlable		= (1 << 1),
	E_Destroyable		= (1 << 2),
	E_Bundlable			= (1 << 3),
};

UENUM(BlueprintType)
enum class FE_EquipmentType : uint8
{
	E_NONE UMETA(Hidden),
	E_Weapon,	 // 무기(방패도 포함 TODO : 따로 BitMask Enum파생)
	E_Head,		 // 머리
	E_Shoulders, // 어깨
	E_Chest,	 // 상의
	E_Legs,		 // 하의
	E_Feet,		 // 신발
	E_Hand,		 // 장갑
	E_Ring,		 // 반지
	E_Necklace,  // 목걸이
	E_Bracelet,  // 팔찌
	E_Anklet,	 // 발찌
	E_Earrings,  // 귀걸이
	E_Belt,      // 벨트
	E_Cloak,     // 망토
	E_Back,      // 등 장비(날개, 망토 등)
	E_Mask,      // 마스크 / 가면
	E_Glasses,   // 안경
	E_EnumMAX  UMETA(Hidden),
};

UENUM(BlueprintType)
enum class FE_ConsumableType : uint8
{
	E_NONE UMETA(Hidden),
	E_Potion,
	E_EnumMAX  UMETA(Hidden),
};