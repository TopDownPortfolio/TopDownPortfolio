#pragma once

#include "CoreMinimal.h"
#include "C_InteractionReceive.h"
#include "C_InteractionReceive_Item.generated.h"

class UStaticMeshComponent;

UCLASS()
class TOPDOWNPORTFOLIO_API UC_InteractionReceive_Item : public UC_InteractionReceive
{
	GENERATED_BODY()
protected:
	UStaticMeshComponent* m_pStaticMesh;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess))
	UMaterialInterface* m_pDetected;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess))
	UMaterialInterface* m_pSelected;
public:
	UC_InteractionReceive_Item();

private:
	void E_SetMaterialInterface(UMaterialInterface* pMaterial);
protected:
virtual void BeginPlay() override;
virtual bool E_BeginEvent_Detect_Implementation(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult) override;
virtual bool E_EndEvent_Detect_Implementation(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex) override;
virtual bool E_InteractionEvent_Implementation(AActor* pInitiator) override;
virtual bool E_SelectedOnEvent_Implementation(AActor* pInitiator, UActorComponent* pInteractionCompo) override;
virtual bool E_SelectedOffEvent_Implementation(AActor* pInitiator, UActorComponent* pInteractionCompo) override;
};
