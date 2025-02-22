#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "GameFramework/Actor.h"
#include "C_InteractionReceive.generated.h"


UCLASS(Abstract)
class TOPDOWNPORTFOLIO_API UC_InteractionReceive : public UActorComponent
{
	GENERATED_BODY()
private:
	enum E_CollisionSize
	{
		E_MaxSize = 5
	};

private:
	TArray< UPrimitiveComponent*> m_arCollsion;
public:
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Interaction, meta = (AllowPrivateAccess = "true"))
	bool m_bDetectTogle;
private:
	UPROPERTY(VisibleAnywhere, Category = Interaction, meta = (AllowPrivateAccess = "true"))
	bool m_bDetected;
public:
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Interaction, meta = (AllowPrivateAccess = "true"))
	bool m_bAutoBeginInteraction;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Interaction, meta = (AllowPrivateAccess = "true"))
	bool m_bAutoEndInteraction;
public:
	UC_InteractionReceive();
	//virtual void BeginPlay() override;

private:
	UFUNCTION()
	void E_BeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);
	UFUNCTION()
	void E_EndOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex);
protected:
	UFUNCTION(BlueprintImplementableEvent)
	bool E_BeginEvent_Detect(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);
	virtual bool E_BeginEvent_Detect_Implementation(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult) { return true; }
	UFUNCTION(BlueprintImplementableEvent)
	bool E_EndEvent_Detect(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex);
	virtual bool E_EndEvent_Detect_Implementation(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex) { return true; }
	UFUNCTION(BlueprintImplementableEvent)
	bool E_BeginEvent_Interaction(AActor* pSrc, UActorComponent* pManageCompo);
	virtual bool E_BeginEvent_Interaction_Implementation(AActor* pSrc, UActorComponent* pManageCompo) { return true; }
	UFUNCTION(BlueprintImplementableEvent)
	bool E_EndEvent_Interaction(AActor* pSrc, UActorComponent* pManageCompo);
	virtual bool E_EndEvent_Interaction_Implementation(AActor* pSrc, UActorComponent* pManageCompo) { return true; }
public:
	UFUNCTION(BlueprintCallable)
	void E_OnOffCollisions(bool bOnOff);
	UFUNCTION(BlueprintPure)
	FName E_GetCollisionTag() { return "T_InteractionReceive"; }
	UFUNCTION(BlueprintPure)
	FName E_GetCollisionProfile() { return "P_InteractionReceive"; } // O_InteractionInitiator
	UFUNCTION(BlueprintCallable)
	void E_BindCollisionOverlaps(UPrimitiveComponent* pCollision);
	UFUNCTION(BlueprintCallable)
	bool E_BeginInteractionEvent(AActor* pSrc, UActorComponent* pManageCompo);
	UFUNCTION(BlueprintCallable)
	bool E_EndInteractionEvent(AActor* pSrc, UActorComponent* pManageCompo);
};

// 상속 모음
//protected:
// virtual bool E_BeginEvent_Detect_Implementation(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult) { return true; }
// virtual bool E_EndEvent_Detect_Implementation(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex) { return true; }
// 
// virtual bool E_BeginEvent_Interaction_Implementation(AActor* pSrc, UActorComponent* pManageCompo) { return false; }
// virtual bool E_EndEvent_Interaction_Implementation(AActor* pSrc, UActorComponent* pManageCompo) { return false; }
