#pragma once

#include "CoreMinimal.h"
#include "O_InputAction.h"
#include "O_InputAction_Move.generated.h"

UCLASS()
class TOPDOWNPORTFOLIO_API UO_InputAction_Move : public UO_InputAction
{
	GENERATED_BODY()
private:

public:
	UO_InputAction_Move();

protected:
	void E_Release();
	virtual void E_Triggered(const FInputActionValue& fInputValue) override;
	virtual void E_Started(const FInputActionValue& fInputValue) override;
	virtual void E_Canceled(const FInputActionValue& fInputValue) override;
	virtual void E_Completed(const FInputActionValue& fInputValue) override;
};
