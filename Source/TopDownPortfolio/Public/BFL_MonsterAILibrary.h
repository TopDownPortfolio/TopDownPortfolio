#pragma once

#include "CoreMinimal.h"
#include "Kismet/BlueprintFunctionLibrary.h"
#include "BFL_MonsterAILibrary.generated.h"

UCLASS()
class TOPDOWNPORTFOLIO_API UBFL_MonsterAILibrary : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()
public:
	UFUNCTION(BlueprintPure, Category = "MonsterAI")
	static FName E_GetName_MonsterState()  { return "eMonsterState"; }

	UFUNCTION(BlueprintPure, Category = "MonsterAI")
	static FName E_GetName_Target()  { return "aTarget"; }

	UFUNCTION(BlueprintPure, Category = "MonsterAI")
	static FName E_GetName_Vector()  { return "oTarget"; }

	UFUNCTION(BlueprintPure, Category = "MonsterAI", Meta = (HidePin = "NodeOwner", DefaultToSelf = "NodeOwner"))
	static uint8 E_GetBBEnum(UBTNode* NodeOwner, FName strKeyName);
	UFUNCTION(BlueprintCallable, Category = "MonsterAI", Meta = (HidePin = "NodeOwner", DefaultToSelf = "NodeOwner"))
	static void E_SetBBEnum(UBTNode* NodeOwner, FName strKeyName, uint8 eEnum);
};
