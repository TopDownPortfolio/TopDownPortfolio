#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "E_State.h"
#include "A_Character_Base.generated.h"

class UC_MontageMGR;
class UC_StatusMGR;
class UC_AttackMGR;
class UC_BuffMGR;
class UCapsuleComponent;
enum class FE_StateType : uint8;

UCLASS()
class TOPDOWNPORTFOLIO_API AA_Character_Base : public ACharacter
{
	GENERATED_BODY()
protected:
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = Montage, meta = (AllowPrivateAccess = "true"))
	UC_MontageMGR* m_pMontageMGR;
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = Status, meta = (AllowPrivateAccess = "true"))
	UC_StatusMGR* m_pStatusMGR;
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = Attack, meta = (AllowPrivateAccess = "true"))
	UC_AttackMGR* m_pAttackMGR;
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = Damage, meta = (AllowPrivateAccess = "true"))
	UCapsuleComponent* m_pDamageCollision;
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = Buff, meta = (AllowPrivateAccess = "true"))
	UC_BuffMGR* m_pBuffMGR;

	UPROPERTY(EditAnyWhere, BlueprintReadWrite, Category = State, meta = (AllowPrivateAccess = "true", Bitmask, BitmaskEnum = FE_StateType))
	uint8 m_eState;
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = Mesh, meta = (AllowPrivateAccess = "true"))
	TArray<FName> m_arHideBone;
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
public:	

	UFUNCTION(BlueprintPure)
	bool E_CheckState(FE_StateType eEnum) { return m_eState & (uint8)eEnum; }
	bool E_CheckState(uint8 eValue) { return E_CheckState((FE_StateType)eValue); }
	UFUNCTION(BlueprintCallable)
	void E_AddState(FE_StateType eEnum);
	void E_AddState(uint8 eValue) { E_AddState((FE_StateType)eValue); }
	UFUNCTION(BlueprintCallable)
	void E_SubState(FE_StateType eEnum);
	void E_SubState(uint8 eValue) { E_SubState((FE_StateType)eValue); }

	virtual bool ShouldTakeDamage(float Damage, FDamageEvent const& DamageEvent, AController* EventInstigator, AActor* DamageCauser) const override;
	virtual void E_Attack(AA_Character_Base* pTarget);
	virtual void E_Defend(float DamageAmount, FDamageEvent const& DamageEvent, AController* EventInstigator, AA_Character_Base* DamageCauser);
	UFUNCTION(BlueprintPure)
	UC_AttackMGR* E_GetAttackMGR() { return m_pAttackMGR; }
	UFUNCTION(BlueprintPure)
	UC_MontageMGR* E_GetMontageMGR() { return m_pMontageMGR; }

	UFUNCTION(BlueprintPure)
	UC_StatusMGR* E_GetStatusMGR() { return m_pStatusMGR; }
};
