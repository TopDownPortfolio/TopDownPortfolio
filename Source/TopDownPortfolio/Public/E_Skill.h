#pragma once

#include "CoreMinimal.h"

UENUM(BlueprintType)
enum class FE_SkillID: uint8
{
	E_NONE UMETA(Hidden),
	E_01,
	E_02,
	E_03,
	E_04,
	E_EnumMAX UMETA(Hidden),
};
