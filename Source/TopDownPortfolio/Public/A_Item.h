#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "E_Item.h"
#include "C_InteractionReceive_Item.h"
#include "A_Item.generated.h"

class UStaticMeshComponent;
class UCapsuleComponent;

UCLASS(BlueprintType)
class TOPDOWNPORTFOLIO_API AA_Item : public AActor
{
	GENERATED_BODY()
private:
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Item, meta = (AllowPrivateAccess = "true"))
	USceneComponent* m_pRoot;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Item, meta = (AllowPrivateAccess = "true"))
	UC_InteractionReceive_Item* m_pInteractionReceive;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Item, meta = (AllowPrivateAccess = "true"))
	UStaticMeshComponent* m_pMeshComponent;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Item, meta = (AllowPrivateAccess = "true"))
	UCapsuleComponent* m_pCollisionComponent;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Item, meta = (AllowPrivateAccess = "true"))
	int nItemID;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Item, meta = (AllowPrivateAccess = "true"))
	int nCount;
public:	
	AA_Item();
	virtual void OnConstruction(const FTransform& Transform) override;
protected:
	virtual void BeginPlay() override;
public:	
};
