#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "G_GameModeBase.generated.h"

class UC_ItemDataTable;

UCLASS()
class TOPDOWNPORTFOLIO_API AG_GameModeBase : public AGameModeBase
{
	GENERATED_BODY()
private:
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = ItemData, meta = (AllowPrivateAccess = "true"))
	UC_ItemDataTable* m_pItemDataTable;
public:
	AG_GameModeBase();
protected:
	virtual void OnConstruction(const FTransform& Transform) override;

public:
	virtual void StartPlay() override;
	UFUNCTION(BlueprintPure, Category = ItemData)
	UC_ItemDataTable* E_GetItemDataTableComponent() { return m_pItemDataTable; }
};
