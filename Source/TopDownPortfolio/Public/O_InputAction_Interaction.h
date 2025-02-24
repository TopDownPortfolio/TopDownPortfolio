#pragma once

#include "CoreMinimal.h"
#include "O_InputAction.h"
#include "O_InputAction_Interaction.generated.h"

class AA_Character_Player;
class UC_InteractionInitiator;

UCLASS()
class TOPDOWNPORTFOLIO_API UO_InputAction_Interaction : public UO_InputAction
{
	GENERATED_BODY()
private:
	AA_Character_Player* m_pPlayer;
	UC_InteractionInitiator* m_pInitiator;
public:
	UO_InputAction_Interaction() = default;
protected:
	virtual void E_Init_After(APlayerController* pController, UInputAction* pInputAction) override;
	virtual void E_Completed(const FInputActionValue& fInputValue) override;
};
