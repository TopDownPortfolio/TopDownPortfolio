#include "O_InputAction.h"

UO_InputAction::UO_InputAction() :
	UObject{}, m_pInputAction{}, m_pController{}, m_arBinding{}, m_eID{}, m_bActive {}
{
	m_bActive = true;
}

void UO_InputAction::E_Init(APlayerController* pController, UInputAction* pInputAction)
{
	if (!pController)
		return;
	m_pController = Cast< AA_PlayerController>( pController);
	if (!m_pController)
		return;
	m_pInputAction = pInputAction;
	E_RemoveActionBinding();
	E_BindAction();
	E_Init_After(m_pController, m_pInputAction);
}

void UO_InputAction::E_Delete()
{
	E_RemoveActionBinding();
}

void UO_InputAction::E_BindAction()
{
	UEnhancedInputComponent* pEnhancedInputComponent = Cast<UEnhancedInputComponent>(m_pController->InputComponent);
	if (!pEnhancedInputComponent)
		return;

	m_arBinding[(uint8)FE_InputTriggerEvent::E_Triggered]	= &pEnhancedInputComponent->BindAction(m_pInputAction, ETriggerEvent::Triggered	, this, &UO_InputAction::E_Triggered_Bind	);
	m_arBinding[(uint8)FE_InputTriggerEvent::E_Started]		= &pEnhancedInputComponent->BindAction(m_pInputAction, ETriggerEvent::Started	, this, &UO_InputAction::E_Started_Bind		);
	m_arBinding[(uint8)FE_InputTriggerEvent::E_Ongoing]		= &pEnhancedInputComponent->BindAction(m_pInputAction, ETriggerEvent::Ongoing	, this, &UO_InputAction::E_Ongoing_Bind		);
	m_arBinding[(uint8)FE_InputTriggerEvent::E_Canceled]	= &pEnhancedInputComponent->BindAction(m_pInputAction, ETriggerEvent::Canceled	, this, &UO_InputAction::E_Canceled_Bind	);
	m_arBinding[(uint8)FE_InputTriggerEvent::E_Completed]	= &pEnhancedInputComponent->BindAction(m_pInputAction, ETriggerEvent::Completed	, this, &UO_InputAction::E_Completed_Bind	);
}

void UO_InputAction::E_RemoveActionBinding()
{
	UEnhancedInputComponent* pEnhancedInputComponent = Cast<UEnhancedInputComponent>(m_pController->InputComponent);
	if (!pEnhancedInputComponent)
	{
		return;
	}

	E_RemoveActionBinding(pEnhancedInputComponent, m_arBinding[(uint8)FE_InputTriggerEvent::E_Triggered]);
	E_RemoveActionBinding(pEnhancedInputComponent, m_arBinding[(uint8)FE_InputTriggerEvent::E_Started]);
	E_RemoveActionBinding(pEnhancedInputComponent, m_arBinding[(uint8)FE_InputTriggerEvent::E_Ongoing]);
	E_RemoveActionBinding(pEnhancedInputComponent, m_arBinding[(uint8)FE_InputTriggerEvent::E_Canceled]);
	E_RemoveActionBinding(pEnhancedInputComponent, m_arBinding[(uint8)FE_InputTriggerEvent::E_Completed]);
}

void UO_InputAction::E_RemoveActionBinding(UEnhancedInputComponent* pEnhancedInputComponent, FEnhancedInputActionEventBinding* pEventBinding)
{
	if (!pEventBinding || !pEnhancedInputComponent)
		return;
	pEnhancedInputComponent->RemoveActionBinding(pEventBinding->GetHandle());
	pEventBinding = nullptr;
}


void UO_InputAction::E_Triggered_Bind(const FInputActionValue& fInputValue)
{
	if (!E_CheckActive())
		return;
	E_Triggered(fInputValue);

}

void UO_InputAction::E_Started_Bind(const FInputActionValue& fInputValue)
{
	if (!E_CheckActive())
		return ;	
	E_Started(fInputValue);

}

void UO_InputAction::E_Ongoing_Bind(const FInputActionValue& fInputValue)
{
	if (!E_CheckActive())
		return ;	
	E_Ongoing(fInputValue);

}

void UO_InputAction::E_Canceled_Bind(const FInputActionValue& fInputValue)
{
	if (!E_CheckActive())
		return ;
	E_Canceled(fInputValue);
}

void UO_InputAction::E_Completed_Bind(const FInputActionValue& fInputValue)
{
	if (!E_CheckActive())
		return ;
	E_Completed(fInputValue);
}

bool UO_InputAction::E_CheckActive()
{
	if (!m_bActive || !m_pController || !m_pController->AcknowledgedPawn)
		return false;
	return true;
}
