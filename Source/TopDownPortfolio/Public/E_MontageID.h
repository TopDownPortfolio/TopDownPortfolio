#pragma once

#include "CoreMinimal.h"
#include "Engine/UserDefinedStruct.h"

UENUM(BlueprintType)
enum class FE_MontageID : uint8
{
	E_NONE UMETA(Hidden),
	E_01,
	E_02,
	E_03,
	E_04,
	E_EnumMAX  UMETA(Hidden),
};