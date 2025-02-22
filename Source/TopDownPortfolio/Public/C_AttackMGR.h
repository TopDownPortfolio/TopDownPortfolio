#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include <list>
#include "C_AttackMGR.generated.h"

class  AA_Attacker;
class AA_Character_Base;
class UT_DamageType;

USTRUCT(BlueprintType)
struct FS_AttackData : public FTableRowBase
{
	GENERATED_USTRUCT_BODY()
public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TSubclassOf< AA_Attacker> cAttackClass;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int nAttackIndex;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FName strSocket;
};


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class TOPDOWNPORTFOLIO_API UC_AttackMGR : public UActorComponent
{
	GENERATED_BODY()
protected:
	DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FD_ChangeTarget, AA_Character_Base*, pOld, AA_Character_Base*, pNew);
private:
	TMap<int, TSet< AA_Character_Base*>> m_mapHitted;
	TMap<int, TArray< AA_Attacker*>> m_mapAttacker;
	AA_Character_Base* m_pOwner;
	AA_Character_Base* m_pTarget;
	float m_fMaxTime;
	float m_fTime;
	TSubclassOf<UDamageType> m_cDamageType;
public:
	//UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = AIActionMGR)
	UPROPERTY(BlueprintCallable, BlueprintAssignable, Category = AttackMGR)
	FD_ChangeTarget On_TargetChange;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = AttackMGR)
	UDataTable* m_pDataTable;
public:
	UC_AttackMGR();

protected:
	virtual void BeginPlay() override;
	//void E_CollisionEnable(std::list<AA_Attacker*>& arList, ECollisionEnabled::Type eType);
	TSet< AA_Character_Base*>* E_GetHitted(int nAttackerIndex);
	TArray< AA_Attacker*>* E_GetAttacker(int nAttackerIndex);
	AA_Attacker* E_SpawnAttacker(TSubclassOf< AA_Attacker> cAttacker);
public:
	virtual void TickComponent(float DeltaTime, enum ELevelTick TickType, FActorComponentTickFunction * ThisTickFunction) override;
	bool E_AddHitted(int nAttackerIndex, AA_Character_Base* pTarget);
	void E_ResetHitted(int nAttackerIndex);
	void E_GetHittedaArray(int nAttackerIndex, TArray<AA_Character_Base*>& arTargets);
	bool E_IsAlreadyHitted(int nAttackerIndex, AA_Character_Base* pTarget);
	TSubclassOf<UDamageType> E_GetDamageType();
	UFUNCTION(BlueprintCallable)
	 void E_SetDamageType(TSubclassOf<UDamageType> cDamageType);
	UFUNCTION(BlueprintCallable)
	void E_SpawnAttacker(FS_AttackData sAttckerData,  AA_Attacker*& arSpawnedAttacker);

	UFUNCTION(BlueprintCallable)
	void E_OnAttack(int nAttackerIndex);
	UFUNCTION(BlueprintCallable)
	void E_EndAttack(int nAttackerIndex);
	
};
