#pragma once

#include "CoreMinimal.h"

UENUM(BlueprintType)
enum class FE_Character: uint8
{
	E_NONE UMETA(Hidden),
	E_01 UMETA(DisplayName = "Player"),
	E_02 UMETA(DisplayName = "Monster01"),
	E_03,
	E_04,
	E_EnumMAX  UMETA(Hidden),
};