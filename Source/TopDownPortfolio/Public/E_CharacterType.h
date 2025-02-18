#pragma once

#include "CoreMinimal.h"

UENUM(BlueprintType)
enum class FE_CharacterType: uint8
{
	E_NONE UMETA(Hidden),
	E_Player UMETA(DisplayName = "Player"),
	E_Monster UMETA(DisplayName = "Monster"),
	E_NPC  UMETA(DisplayName = "NPC"),
	E_EnumMAX  UMETA(Hidden),
}; 

UENUM(BlueprintType)
enum class FE_Affiliation : uint8
{
	E_NONE UMETA(Hidden),
	E_Enemy,
	E_Neutral,
	E_Friend,
	E_EnumMAX  UMETA(Hidden),
};

class C_CharacterType
{
private:
	C_CharacterType() = default;
	~C_CharacterType() = default;
public:
	static FE_Affiliation E_GetAffiliation(FE_CharacterType eSrc, FE_CharacterType eDst);
};