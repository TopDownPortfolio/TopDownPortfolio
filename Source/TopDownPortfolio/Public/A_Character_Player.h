#pragma once

#include "CoreMinimal.h"
#include "A_Character_Base.h"
#include "S_Buff.h"
#include "A_Character_Player.generated.h"

class UCameraComponent;
class USpringArmComponent;
class UChildActorComponent;
class AA_Attacker;
struct FS_BuffData_Status;
enum class FE_SkillID :uint8;

UCLASS(Blueprintable)
class AA_Character_Player : public AA_Character_Base
{
	GENERATED_BODY()
protected:
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera, meta = (AllowPrivateAccess = "true"))
	UCameraComponent* m_pCameraComponent;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera, meta = (AllowPrivateAccess = "true"))
	USpringArmComponent* m_pCameraBoom;
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = Status, meta = (AllowPrivateAccess = "true"))
	FS_BuffData_Status m_sMp;
public:
	AA_Character_Player();
	FORCEINLINE UCameraComponent* GetTopDownCameraComponent() const { return m_pCameraComponent; }
	FORCEINLINE USpringArmComponent* GetCameraBoom() const { return m_pCameraBoom; }
	virtual void OnConstruction(const FTransform& Transform) override;

protected:
	virtual void BeginPlay() override;
	FName E_GetWeaponRSocketName() { return "Weapon_r"; }
	FName E_GetWeaponLSocketName() { return "Weapon_l"; }

private:
	void E_Init_Pawn();
	void E_Init_CameraBoom();
	void E_Init_CameraComponent();
	void E_Init_CharacterMovement();

};