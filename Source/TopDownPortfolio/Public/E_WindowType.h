#pragma once
#include "CoreMinimal.h"

UENUM(BlueprintType)
enum class FE_WindowID: uint8
{
	E_NONE UMETA(Hidden),
	E_Main,
	E_Skill,
	E_Inventory,
	E_PlayerActionBar,
	E_MonsterActionBar,
	E_EnumMAX UMETA(Hidden),
};

UENUM(BlueprintType)
enum class FE_WindowSetting : uint8
{
	E_AnchorsMin,
	E_AnchorsMax,
	E_WidgetPosition,
	E_WidgetSize,
	E_EnumMax UMETA(Hidden),
};