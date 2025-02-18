#pragma once

#include "CoreMinimal.h"

UENUM(BlueprintType)
enum class FE_AIActionType : uint8
{
	E_NONE UMETA(Hidden),
	E_Montage,
	E_EnumMAX UMETA(Hidden),
};