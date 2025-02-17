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

class TOPDOWNPORTFOLIO_API E_WindowType
{
private:
	E_WindowType() = delete;
	~E_WindowType() = delete;
};
