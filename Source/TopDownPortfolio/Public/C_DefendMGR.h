#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "C_DefendMGR.generated.h"

class AA_Character_Base;
class AController;
class UC_StatusMGR;
enum class FE_DamageEventType : uint8;

UENUM(BlueprintType)
enum class FE_DefendType : uint8
{
	E_Default,
	E_EnumMAX UMETA(Hidden),
};

UENUM(BlueprintType)
enum class FE_ApplyStatus: uint8
{
	E_Hp,
	E_Sheild,
	E_EnumMAX UMETA(Hidden),
};

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class TOPDOWNPORTFOLIO_API UC_DefendMGR : public UActorComponent
{
	GENERATED_BODY()
public:
	DECLARE_DYNAMIC_MULTICAST_DELEGATE(FD_OnStartDamaged);
	DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FD_OnEndDamaged, float, fDamagedAmount, FE_DamageEventType, eDmamgeType);
protected:
	AA_Character_Base* m_pOwner;
	UC_StatusMGR* m_pStatus;
	FE_DamageEventType m_eDmamgeType;
public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = DefendMGR)
	FE_DefendType m_eDefendType;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = DefendMGR)
	FE_ApplyStatus m_eApplyStatus;
	UPROPERTY(BlueprintCallable, BlueprintAssignable)
	FD_OnStartDamaged On_StartDamage;
	UPROPERTY(BlueprintCallable, BlueprintAssignable)
	FD_OnEndDamaged On_EndDamage;	
public:	
	UC_DefendMGR();

private:
	float E_Calcul_Default(float fDamageAmount);
	float E_ApplyStatus(FE_ApplyStatus eApplyStatus, float fDamageAmount);
protected:
	virtual void BeginPlay() override;
	float E_CalculDmage(FE_DefendType eDefendType, float fDamageAmount);
	void E_DamageEvent(float fDamageAmount, FDamageEvent const& DamageEvent);
public:	

	UFUNCTION(BlueprintPure)
	FE_DamageEventType E_GetDamagedType() { return m_eDmamgeType; }
	bool E_Defend(float DamageAmount, FDamageEvent const& DamageEvent, AController* EventInstigator, AA_Character_Base* DamageCauser);
};
