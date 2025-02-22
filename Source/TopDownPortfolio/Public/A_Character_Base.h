#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "C_StateMGR.h"
#include "C_MontageMGR.h"
#include "C_AttackMGR.h"
#include "C_DefendMGR.h"
#include "A_Character_Base.generated.h"

class UC_StatusMGR;
class UC_BuffMGR;
class UCapsuleComponent;

UCLASS()
class TOPDOWNPORTFOLIO_API AA_Character_Base : public ACharacter
{
	GENERATED_BODY()
protected:
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = MontageMGR, meta = (AllowPrivateAccess = "true"))
	UC_MontageMGR* m_pMontageMGR;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = StatusMGR, meta = (AllowPrivateAccess = "true"))
	UC_StatusMGR* m_pStatusMGR;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = AttackMGR, meta = (AllowPrivateAccess = "true"))
	UC_AttackMGR* m_pAttackMGR;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = DamageCollision, meta = (AllowPrivateAccess = "true"))
	UCapsuleComponent* m_pDamageCollision;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = BuffMGR, meta = (AllowPrivateAccess = "true"))
	UC_BuffMGR* m_pBuffMGR;
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = Mesh, meta = (AllowPrivateAccess = "true"))
	TArray<FName> m_arHideBone;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = StateMGR, meta = (AllowPrivateAccess = "true"))
	UC_StateMGR* m_pStateMGR;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = DefendMGR, meta = (AllowPrivateAccess = "true"))
	UC_DefendMGR* m_pDefendMGR;
public:
	AA_Character_Base();
	virtual void OnConstruction(const FTransform& Transform) override;

	//virtual void Tick(float DeltaTime) override;
	//virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

protected:
	virtual void BeginPlay() override;
protected:
	void E_RegisterComponent(UActorComponent* pComponent);
	FName E_GetDamageCollisionProfile() { return "P_Defend"; }
	void E_HideSocket();
	UFUNCTION()
	void E_SwitchMode();
public:	
	//virtual bool ShouldTakeDamage(float Damage, FDamageEvent const& DamageEvent, AController* EventInstigator, AActor* DamageCauser) const override;
	virtual bool E_Attack(AA_Character_Base* pTarget);
	virtual bool E_Defend(float DamageAmount, FDamageEvent const& DamageEvent, AController* EventInstigator, AA_Character_Base* DamageCauser);
	UFUNCTION(BlueprintPure)
	UC_AttackMGR* E_GetAttackMGR() { return m_pAttackMGR; }
	UFUNCTION(BlueprintPure)
	UC_MontageMGR* E_GetMontageMGR() { return m_pMontageMGR; }

	UFUNCTION(BlueprintPure)
	UC_StatusMGR* E_GetStatusMGR() { return m_pStatusMGR; }
	UFUNCTION(BlueprintPure)
	UC_StateMGR* E_GetStateMGR() { return m_pStateMGR; }
	UFUNCTION(BlueprintPure)
	UC_DefendMGR* E_GetDefendMGR() { return m_pDefendMGR; }
};
