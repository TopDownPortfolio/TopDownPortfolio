#include "A_Attacker_Spawn.h"
#include "A_Character_Base.h"
#include "C_StatusMGR.h"
#include "Engine/DamageEvents.h"

AA_Attacker_Spawn::AA_Attacker_Spawn() :
	AA_Attacker{}
{
}
//
//void AA_Attacker_Spawn::E_On()
//{
//	E_SetAttackCollisionEnabled(ECollisionEnabled::QueryOnly);
//}
//
//void AA_Attacker_Spawn::E_Off()
//{
//	/*float fDamage = m_pOwner->E_GetStatusMGR()->E_GetStatus_Current(FE_StatusID::E_ATTACK);
//	FDamageEvent fDamageEvent{};
//	for (AA_Character_Base* pTarget : m_setTarget)
//	{
//		pTarget->TakeDamage(fDamage, fDamageEvent, m_pOwner->GetController(), m_pOwner);
//	}
//	m_setTarget.Reset();*/
//	E_SetAttackCollisionEnabled(ECollisionEnabled::NoCollision);
//}
//
