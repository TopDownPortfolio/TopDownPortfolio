#pragma once

#include "CoreMinimal.h"
#include "A_Interaction.h"
#include "A_Interaction_StoreNPC.generated.h"

class UC_InteractionReceive_Store;
class UC_Store;
class UCapsuleComponent;

UCLASS()
class TOPDOWNPORTFOLIO_API AA_Interaction_StoreNPC : public AA_Interaction
{
	GENERATED_BODY()
private:
	UPROPERTY(VisibleAnywhere, Category = Item, meta = (AllowPrivateAccess = "true"))
	UC_InteractionReceive_Store* m_pInteractionReceiveStore;
	UPROPERTY(VisibleAnywhere, Category = Item, meta = (AllowPrivateAccess = "true"))
	UC_Store* m_pStore;
	UPROPERTY(VisibleAnywhere, Category = Item, meta = (AllowPrivateAccess = "true"))
	UCapsuleComponent* m_pCollisionComponent;
	UPROPERTY(VisibleAnywhere, Category = Item, meta = (AllowPrivateAccess = "true"))
	USkeletalMeshComponent* m_pNPCMesh;
public:
	AA_Interaction_StoreNPC();

public:
	virtual void BeginPlay() override;
	UC_Store* E_GetStoreComponent();
protected:
	void OnConstruction(const FTransform& Transform);

};
