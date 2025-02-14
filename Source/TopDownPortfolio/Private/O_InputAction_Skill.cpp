#include "O_InputAction_Skill.h"

UO_InputAction_Skill::UO_InputAction_Skill() :
	UO_InputAction{}
{
}

void UO_InputAction_Skill::E_Started(const FInputActionValue& fInputValue)
{
	if (!m_pController || !m_bActive)
		return;
	FE_SkillID eID = m_pController->E_GetSkillID(m_eID);
	m_pController->E_Action(eID);
}

