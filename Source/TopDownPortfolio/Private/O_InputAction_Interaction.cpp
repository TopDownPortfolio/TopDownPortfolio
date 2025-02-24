#include "O_InputAction_Interaction.h"
#include "A_Character_Player.h"
#include "C_InteractionInitiator.h"

void UO_InputAction_Interaction::E_Init_After(APlayerController* pController, UInputAction* pInputAction)
{
	m_pPlayer = Cast<AA_Character_Player>(m_pController->AcknowledgedPawn);
	if (!m_pPlayer)
	{
		m_bActive = false;
		return;
	}
	m_pInitiator = m_pPlayer->E_GetInteractionInitiator();
}

void UO_InputAction_Interaction::E_Completed(const FInputActionValue& fInputValue)
{
	AA_Interaction* pResult{};
	m_pInitiator->E_Interaction(pResult);
}
