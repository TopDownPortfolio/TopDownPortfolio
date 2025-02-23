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
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Interaction, meta = (AllowPrivateAccess = "true"))
	bool m_bSelectableTogle;
protected:
	UPROPERTY(VisibleAnywhere, Category = Interaction, meta = (AllowPrivateAccess = "true"))
	bool m_bDetected;
	UPROPERTY(VisibleAnywhere, Category = Interaction, meta = (AllowPrivateAccess = "true"))
	bool m_bSelected;
public:
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Interaction, meta = (AllowPrivateAccess = "true"))
	bool m_bAutoBeginInteraction;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Interaction, meta = (AllowPrivateAccess = "true"))
	bool m_bAutoEndInteraction;
protected:
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Interaction, meta = (AllowPrivateAccess = "true"))
	bool m_bInteractionResult;

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
	UFUNCTION(BlueprintImplementableEvent)
	bool E_EndEvent_Detect(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex);
	UFUNCTION(BlueprintImplementableEvent)
	bool E_BeginEvent_Interaction(AActor* pInitiator, UActorComponent* pInteractionCompo);
	UFUNCTION(BlueprintImplementableEvent)
	bool E_EndEvent_Interaction(AActor* pInitiator, UActorComponent* pInteractionCompo);
	UFUNCTION(BlueprintImplementableEvent)
	bool E_InteractionEvent(AActor* pInitiator);
	UFUNCTION(BlueprintImplementableEvent)
	bool E_SelectedOnEvent(AActor* pInitiator, UActorComponent* pInteractionCompo);
	UFUNCTION(BlueprintImplementableEvent)
	bool E_SelectedOffEvent(AActor* pInitiator, UActorComponent* pInteractionCompo);
	UFUNCTION(BlueprintImplementableEvent)
	bool E_InteractionStart(AActor* pInitiator);
	UFUNCTION(BlueprintImplementableEvent)
	bool E_InteractionEnd(AActor* pInitiator);

	virtual bool E_BeginEvent_Detect_Implementation(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult) { return true; }
	virtual bool E_EndEvent_Detect_Implementation(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex) { return true; }
	virtual bool E_BeginEvent_Interaction_Implementation(AActor* pInitiator, UActorComponent* pInteractionCompo) { return true; }
	virtual bool E_EndEvent_Interaction_Implementation(AActor* pInitiator, UActorComponent* pInteractionCompo) { return true; }
	virtual bool E_InteractionEvent_Implementation(AActor* pInitiator) { return true; }
	virtual bool E_SelectedOnEvent_Implementation(AActor* pInitiator, UActorComponent* pInteractionCompo) { return true; }
	virtual bool E_SelectedOffEvent_Implementation(AActor* pInitiator, UActorComponent* pInteractionCompo) { return true; }
	virtual bool E_InteractionStart_Implementation(AActor* pInitiator) { return true; }
	virtual bool E_InteractionEnd_Implementation(AActor* pInitiator)  { return true; }
public:
	UFUNCTION(BlueprintPure)
	FName E_GetCollisionTag() { return "T_InteractionReceive"; }
	UFUNCTION(BlueprintPure)
	FName E_GetCollisionProfile() { return "P_InteractionReceive"; } // O_InteractionInitiator
	UFUNCTION(BlueprintCallable)
	void E_BindCollisionOverlaps(UPrimitiveComponent* pCollision);
	UFUNCTION(BlueprintCallable)
	void E_OnOffCollisions(bool bOnOff);
	UFUNCTION(BlueprintCallable)
	bool E_Interaction(AActor* pInitiator);
	UFUNCTION(BlueprintCallable)
	bool E_Selected(AActor* pInitiator, UActorComponent* pInteractionCompo, bool bOnOffDettected);
};