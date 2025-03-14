#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "S_Item.h"
#include "C_Store.generated.h"

class UW_StoreSlot;
class UScrollBox;

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class TOPDOWNPORTFOLIO_API UC_Store : public UActorComponent
{
	GENERATED_BODY()
public:
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Store)
	TArray<FS_ItemStoreData> m_arStoreData;
	TArray<UW_StoreSlot*> m_arWidget;
public:	
	UC_Store();
protected:
	virtual void BeginPlay() override;
private:
	void E_CreateWidget(FS_ItemStoreData& sSrc, UW_StoreSlot*& pDst);

public:
	void E_AddToStoreWidget(UScrollBox* pScrollBox, APlayerController* pPlayer);
	void E_EraseStroeWidget(UScrollBox* pScrollBox);
};
