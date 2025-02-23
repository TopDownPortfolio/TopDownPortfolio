#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "C_Inventory.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class TOPDOWNPORTFOLIO_API UC_Inventory : public UActorComponent
{
	GENERATED_BODY()
private:


public:	
	UC_Inventory();

protected:
	virtual void BeginPlay() override;

public:	
		
};
