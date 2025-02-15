#pragma once

#include "CoreMinimal.h"
#include "O_InputAction.h"
#include "O_InputAction_WidgetClose.generated.h"

UCLASS()
class TOPDOWNPORTFOLIO_API UO_InputAction_WidgetClose : public UO_InputAction
{
	GENERATED_BODY()
public:
	UO_InputAction_WidgetClose();
	virtual void E_Completed(const FInputActionValue& fInputValue) override;
};
