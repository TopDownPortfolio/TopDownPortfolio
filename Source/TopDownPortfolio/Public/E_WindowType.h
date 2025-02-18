#pragma once
#include "CoreMinimal.h"

UENUM(BlueprintType)
enum class FE_WindowID: uint8
{
	E_NONE UMETA(Hidden),
	E_Skill,
	E_Inventory,
	E_EnumMAX UMETA(Hidden),
};