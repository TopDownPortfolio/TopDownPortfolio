#pragma once

#include "CoreMinimal.h"

UENUM(BlueprintType)
enum class FE_InputActionID : uint8
{
	E_NONE UMETA(Hidden),
	E_RMouseClick,
	E_LMouseClick,
	E_Q,
	E_W,
	E_E,
	E_SkillWindow,
	E_EnumMAX  UMETA(Hidden)
};

class TOPDOWNPORTFOLIO_API E_InputActionID
{
private:
	E_InputActionID() = delete;
	~E_InputActionID() = delete;
};
