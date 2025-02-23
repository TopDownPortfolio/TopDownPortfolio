#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "C_InteractionReceive.h"
#include "A_Interaction.generated.h"

UCLASS()
class TOPDOWNPORTFOLIO_API AA_Interaction : public AActor
{
	GENERATED_BODY()
protected:
	UPROPERTY(VisibleAnywhere, Category = Item, meta = (AllowPrivateAccess = "true"))
	USceneComponent* m_pRoot;
	UC_InteractionReceive* m_pInteractionReceive;
public:	
	AA_Interaction();

protected:
	virtual void BeginPlay() override;

	void OnConstruction(const FTransform& Transform);

public:	

	UFUNCTION(BlueprintPure)
	void E_GetInteractionReceive(UC_InteractionReceive*& InteractionReceive) { InteractionReceive = m_pInteractionReceive; }
};
