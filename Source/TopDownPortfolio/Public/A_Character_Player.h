#pragma once

#include "CoreMinimal.h"
#include "A_Character_Base.h"
#include "A_Character_Player.generated.h"

class UCameraComponent;
class USpringArmComponent;
class UChildActorComponent;
class UC_SkillMGR;

UCLASS(Blueprintable)
class AA_Character_Player : public AA_Character_Base
{
	GENERATED_BODY()
protected:
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera, meta = (AllowPrivateAccess = "true"))
	UCameraComponent* m_pCameraComponent;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera, meta = (AllowPrivateAccess = "true"))
	USpringArmComponent* m_pCameraBoom;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = Attack, meta = (AllowPrivateAccess = "true"))
	UChildActorComponent* m_pWeaponR;

	AA_Character_Base* m_pTarget;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = Attack, meta = (AllowPrivateAccess = "true"))
	UC_SkillMGR* m_pSkillMGR;
public:
	AA_Character_Player();
	FORCEINLINE UCameraComponent* GetTopDownCameraComponent() const { return m_pCameraComponent; }
	FORCEINLINE USpringArmComponent* GetCameraBoom() const { return m_pCameraBoom; }
	virtual void OnConstruction(const FTransform& Transform) override;

	UFUNCTION(BlueprintPure)
	AA_Character_Base* E_GetTarget() { return m_pTarget; }
	UFUNCTION(BlueprintPure)
	UC_SkillMGR* E_GetSkillMGR() { return m_pSkillMGR; }
protected:
	virtual void BeginPlay() override;
	FName E_GetWeaponRSocketName() { return "Weapon_r"; }
	FName E_GetWeaponLSocketName() { return "Weapon_l"; }

private:
	void E_Init_Pawn();
	void E_Init_CameraBoom();
	void E_Init_CameraComponent();
	void E_Init_CharacterMovement();


public:
	virtual void E_Attack(AA_Character_Base* pTarget) override;
	
	virtual void E_Action_Implementation(FE_SkillID eID) override;

};