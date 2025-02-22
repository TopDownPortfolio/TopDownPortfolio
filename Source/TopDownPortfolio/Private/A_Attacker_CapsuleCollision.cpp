#include "A_Attacker_CapsuleCollision.h"
#include "Components/CapsuleComponent.h"

AA_Attacker_CapsuleCollision::AA_Attacker_CapsuleCollision() :
	AA_Attacker{}, m_pCollision{}
{
	m_pCollision = CreateDefaultSubobject<UCapsuleComponent>("AttackCollision");
	m_pCollision->AttachToComponent(GetRootComponent(), FAttachmentTransformRules::KeepRelativeTransform);
	m_pCollision->ComponentTags.Add(E_GetCollisionTag());
	m_arCollision.Init(m_pCollision, 1);
}
