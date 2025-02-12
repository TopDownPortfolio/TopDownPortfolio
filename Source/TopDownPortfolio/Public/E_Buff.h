#pragma once

#include "CoreMinimal.h"

UENUM(BlueprintType)
enum class FE_BuffID : uint8
{
	E_NONE UMETA(Hidden),
	E_Base,
	E_Status,
	E_EnumMAX UMETA(Hidden),
};




class TOPDOWNPORTFOLIO_API E_Buff
{
private:
	E_Buff() = delete;
	~E_Buff() = delete;
};
