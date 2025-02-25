#pragma once

#include "CoreMinimal.h"
#include "Kismet/BlueprintFunctionLibrary.h"
#include "E_Item.h"
#include "BFL_ItemLibrary.generated.h"

class AG_GameModeBase;
class UC_ItemDataTable;

UCLASS()
class TOPDOWNPORTFOLIO_API UBFL_ItemLibrary : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()
private:
	static AG_GameModeBase* E_GetGameModeBase(const UObject* WorldContextObject);
	static UC_ItemDataTable* E_GetItemDataTable(const UObject* WorldContextObject);

public:
	UFUNCTION(BlueprintPure, Category = "ItemData")
	static void  E_GetItemName(const UObject* WorldContextObject, FE_ItemType eItemType, int nItemID, FName& ItemName);
	UFUNCTION(BlueprintPure, Category = "ItemData")
	static void E_GetItemFlag(const UObject* WorldContextObject, FE_ItemType eItemType, int nItemID, uint8& nItemFlag);
	UFUNCTION(BlueprintPure, Category = "ItemData")
	static void  E_GetItemTexture(const UObject* WorldContextObject, FE_ItemType eItemType, int nItemID, UTexture2D*& pItemTexture);
	UFUNCTION(BlueprintPure, Category = "ItemData")
	static void E_GetItemStaticMesh(const UObject* WorldContextObject, FE_ItemType eItemType, int nItemID, UStaticMesh*& pItemStaticMesh);
	UFUNCTION(BlueprintPure, Category = "ItemData")
	static void E_GetItemDesc(const UObject* WorldContextObject, FE_ItemType eItemType, int nItemID, FName& ItemDesc);

};
