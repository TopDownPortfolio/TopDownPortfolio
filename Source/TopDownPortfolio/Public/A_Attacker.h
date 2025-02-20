#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "C_AttackMGR.h"
#include "A_Attacker.generated.h"

class AA_Character_Base;

UCLASS()
class TOPDOWNPORTFOLIO_API AA_Attacker : public AActor
{
	GENERATED_BODY()
protected:
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category= Attacker, meta = (AllowPrivateAccess = "true"))
	USceneComponent* m_pRoot;
	TArray<UPrimitiveComponent*> m_arCollision; // save collision
	AA_Character_Base* m_pOwner;
	UC_AttackMGR* m_pAttackMGR;
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = Attacker, meta = (AllowPrivateAccess = "true"))
	int m_nAttackIndex;
public:	
	AA_Attacker();
	//virtual void OnConstruction(const FTransform& Transform) override;

	UFUNCTION()
	void E_Destroy( AActor* DestroyedActor);
protected:
	virtual void BeginPlay() override;
	UFUNCTION()
	void E_BeginOverlap( UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);
	bool E_SetOwner();
	bool E_SetAttackMGR();
	virtual bool E_CheckOverlap(AActor* pTarget);
	virtual void E_OverlapEvent(AActor* pTarget);
	virtual void E_On() {}
	virtual void E_Off() {}
public:	
	virtual void E_Init(AA_Character_Base* pOwner, FName strSocket);
	UFUNCTION(BlueprintPure)
	int E_GetAttackIndex() { return m_nAttackIndex;	}

	UFUNCTION(BlueprintCallable)
	void E_OnAttack();
	UFUNCTION(BlueprintCallable)
	void E_OffAttack();

	UFUNCTION(BlueprintCallable)
	void E_OnOfCollisionEnabled(ECollisionEnabled::Type eEnable = ECollisionEnabled::QueryOnly);
	UFUNCTION(BlueprintPure)
	FName E_GetCollisionTag() { return "T_Attack"; }
	UFUNCTION(BlueprintPure)
	FName E_GetCollisionProfile() { return "P_Attack"; }
};
