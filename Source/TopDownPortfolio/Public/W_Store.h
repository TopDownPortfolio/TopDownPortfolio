#pragma once

#include "CoreMinimal.h"
#include "W_WindowBase.h"
#include "W_Store.generated.h"

class UScrollBox;

UCLASS()
class TOPDOWNPORTFOLIO_API UW_Store : public UW_WindowBase
{
	GENERATED_BODY()
protected:
	UPROPERTY(BlueprintReadWrite, meta = (BindWidget, AllowPrivateAccess ="TRUE"))
	UScrollBox* pScrollBoxSlot;
public:
	UW_Store(const FObjectInitializer& ObjectInitializer);
	UScrollBox* E_GetScrollBox();
};
