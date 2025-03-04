#pragma once

#include "CoreMinimal.h"
#include "C_InteractionReceive.h"
#include "C_InteractionReceive_Store.generated.h"

class UC_Store;
class  UW_Store;
class UC_WidgetMGR;

UCLASS()
class TOPDOWNPORTFOLIO_API UC_InteractionReceive_Store : public UC_InteractionReceive
{
	GENERATED_BODY()
private:
	UC_Store* m_pStore;  
	UW_Store* m_pStoreWidget;
	UC_WidgetMGR* m_pWidgetMGR;
public:
	UC_InteractionReceive_Store();

protected:
	virtual void BeginPlay() override;

protected:
	//virtual bool E_BeginEvent_Detect_Implementation(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult) override;
	virtual bool E_EndEvent_Detect_Implementation(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex) override;
	//virtual bool E_BeginEvent_Interaction_Implementation(AActor* pInitiator, UActorComponent* pInteractionCompo) override;
	//virtual bool E_EndEvent_Interaction_Implementation(AActor* pInitiator, UActorComponent* pInteractionCompo) override;
	virtual bool E_InteractionEvent_Implementation(AActor* pInitiator) override;
	//virtual bool E_SelectedOnEvent_Implementation(AActor* pInitiator, UActorComponent* pInteractionCompo) override;
	//virtual bool E_SelectedOffEvent_Implementation(AActor* pInitiator, UActorComponent* pInteractionCompo) override;
	//virtual bool E_InteractionStart_Implementation(AActor* pInitiator) override;
	//virtual bool E_InteractionEnd_Implementation(AActor* pInitiator) override;
};
