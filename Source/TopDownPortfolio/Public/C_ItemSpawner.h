#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "S_Item.h"
#include "C_ItemSpawner.generated.h"

class AA_Interaction_Item;

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class TOPDOWNPORTFOLIO_API UC_ItemSpawner : public UActorComponent
{
	GENERATED_BODY()
public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = ItemSpawn)
	TArray< FS_ItemInstanceData> m_arSpawnItemData;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = ItemSpawn)
	TSubclassOf< AA_Interaction_Item> m_cSpawnItemActor;
public:	
	UC_ItemSpawner();

	virtual void EndPlay(const EEndPlayReason::Type EndPlayReason) override;
};
