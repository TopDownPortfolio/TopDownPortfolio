#include "O_InputAction_WidgetClose.h"

UO_InputAction_WidgetClose::UO_InputAction_WidgetClose() : 
	UO_InputAction{}
{
}

void UO_InputAction_WidgetClose::E_Completed(const FInputActionValue& fInputValue)
{
	if (!m_bActive || !m_pController)
		return;
	m_pController->E_GetWidgetMGR()->E_UnRegisterWidget();
}
