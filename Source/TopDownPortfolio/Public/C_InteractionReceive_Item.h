#pragma once

#include "CoreMinimal.h"
#include "C_InteractionReceive.h"
#include "C_InteractionReceive_Item.generated.h"

UCLASS()
class TOPDOWNPORTFOLIO_API UC_InteractionReceive_Item : public UC_InteractionReceive
{
	GENERATED_BODY()

public:
	UC_InteractionReceive_Item();

protected:
	virtual bool E_BeginEvent_Detect_Implementation(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult) override;
	virtual bool E_EndEvent_Detect_Implementation(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex) override;
	virtual bool E_BeginEvent_Interaction_Implementation(AActor* pSrc, UActorComponent* pManageCompo) override;
};
