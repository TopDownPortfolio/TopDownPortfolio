#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include <queue>
#include "C_InteractionInitiator.generated.h"

class AA_Interaction;

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class TOPDOWNPORTFOLIO_API UC_InteractionInitiator : public UActorComponent
{
	GENERATED_BODY()
private:
	enum E_CollisionSize
	{
		E_MaxSize = 5
	};
private:
	TArray< UPrimitiveComponent*> m_arCollsion;
	TSet<AA_Interaction*> m_setInteractionReceive;
	std::queue< AA_Interaction*> m_queReceive;
	AA_Interaction* m_pFirst;
public:
	UC_InteractionInitiator();
protected:
	virtual void BeginPlay() override;
private:

	UFUNCTION()
	void E_BeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);
	UFUNCTION()
	void E_EndOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex);
	bool E_AddActor(AA_Interaction* pInteraction);
	bool E_RemoveActor(AA_Interaction* pInteraction);
	bool E_SetFirst();
protected:
	AA_Interaction* E_GetInteractionActor(AActor* pInteraction);

	AA_Interaction* E_GetFirst();
public:
	UFUNCTION(BlueprintCallable)
	bool E_Interaction(AA_Interaction*& pInteractedActor);
	UFUNCTION(BlueprintCallable)
	void E_BindCollisionOverlaps(UPrimitiveComponent* pCollision);
	UFUNCTION(BlueprintPure)
	FName E_GetCollisionTag() { return "T_InteractionInitiator"; }
	UFUNCTION(BlueprintPure)
	FName E_GetCollisionProfile() { return "P_InteractionInitiator"; }
};
