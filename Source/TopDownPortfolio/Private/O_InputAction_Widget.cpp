#include "O_InputAction_Widget.h"
#include "C_WidgetMGR.h"

UO_InputAction_Widget::UO_InputAction_Widget() :
	UO_InputAction{}
{
}

void UO_InputAction_Widget::E_Completed(const FInputActionValue& fInputValue)
{
	if (!m_bActive || !m_pController)
		return;
	m_pController->E_GetWidgetMGR()->E_RegisterWidget(m_pController->E_GetWidgetID(m_eID));
}
