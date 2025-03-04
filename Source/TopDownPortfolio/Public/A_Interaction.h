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
	UActorComponent* m_pActionComponent;
public:	
	AA_Interaction();
	UActorComponent* E_GetActionComponent() { return m_pActionComponent; }
	UFUNCTION(BlueprintPure)
	void E_GetActionComponent(UActorComponent*& ActionComponent) { ActionComponent = m_pActionComponent; }
	UFUNCTION(BlueprintPure)
	void E_GetInteractionReceive(UC_InteractionReceive*& InteractionReceive) { InteractionReceive = m_pInteractionReceive; }
};
