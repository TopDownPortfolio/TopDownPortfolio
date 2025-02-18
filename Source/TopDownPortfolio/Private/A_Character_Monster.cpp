#include "A_Character_Monster.h"
#include "C_AIActionMGR.h"

AA_Character_Monster::AA_Character_Monster() :
	AA_Character_Base{}, m_pAIAction{}
{
	m_pAIAction = CreateDefaultSubobject<UC_AIActionMGR>("AIActionMGR");
	m_eCharacterType = FE_CharacterType::E_Monster;
}

void AA_Character_Monster::OnConstruction(const FTransform& Transform)
{
	AA_Character_Base::OnConstruction(Transform);
	E_RegisterComponent(m_pAIAction);
}
