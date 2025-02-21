#pragma once

#include "CoreMinimal.h"
#include "GameFramework/DamageType.h"
#include "T_DamageType.generated.h"


UENUM(BlueprintType)
enum class FE_DamageEventType : uint8
{
	E_NONE UMETA(Hidden),
	E_KnockBack,
	E_KnockDown,
	E_Stun,
	E_EnumMAX  UMETA(Hidden)
};

UCLASS(const, Blueprintable, BlueprintType)
class TOPDOWNPORTFOLIO_API UT_DamageType : public UDamageType 
{
	GENERATED_BODY()
public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = DamageType)
	FE_DamageEventType eDamageEventType;
};
