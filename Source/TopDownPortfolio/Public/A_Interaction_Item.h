#pragma once

#include "CoreMinimal.h"
#include "A_Interaction.h"
#include "E_Item.h"
#include "A_Interaction_Item.generated.h"

class UCapsuleComponent;
class UStaticMeshComponent;
class UC_InteractionReceive_Item;

UCLASS()
class TOPDOWNPORTFOLIO_API AA_Interaction_Item : public AA_Interaction
{
	GENERATED_BODY()
private:
	UPROPERTY(VisibleAnywhere, Category = Item, meta = (AllowPrivateAccess = "true"))
	UC_InteractionReceive_Item* m_pInteractionReceiveItem;
	UPROPERTY(VisibleAnywhere, Category = Item, meta = (AllowPrivateAccess = "true"))
	UStaticMeshComponent* m_pMeshComponent;
	UPROPERTY(VisibleAnywhere, Category = Item, meta = (AllowPrivateAccess = "true"))
	UCapsuleComponent* m_pCollisionComponent;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Item, meta = (AllowPrivateAccess = "true"))
	int m_nItemID;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Item, meta = (AllowPrivateAccess = "true"))
	int m_nCount;
public:
	AA_Interaction_Item();
	virtual void OnConstruction(const FTransform& Transform) override;
protected:
	virtual void BeginPlay() override;
public:
	UStaticMeshComponent* E_GetStaticMeshComponent() { return m_pMeshComponent; }

	int E_GetItemID() { return  m_nItemID;	}
	int E_GetItemCount() { return  m_nCount;	}
	UFUNCTION(BlueprintPure)
	void E_GetItemID(int& nItemID) { nItemID = m_nItemID;	}
	UFUNCTION(BlueprintPure)
	void E_GetItemCount(int& nItemCount) { nItemCount = m_nCount;	}
};
