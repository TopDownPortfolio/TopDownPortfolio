#include "A_Attacker_StaticMesh.h"
#include "Components/CapsuleComponent.h"
#include "A_Character_Base.h"
#include "Components/SkeletalMeshComponent.h"
#include "Components/StaticMeshComponent.h"

AA_Attacker_StaticMesh::AA_Attacker_StaticMesh() :
	AA_Attacker{}, m_pMesh{}, m_pCollision{}
{
	m_pMesh = CreateDefaultSubobject<UStaticMeshComponent>("StaticMesh");
	m_pCollision = CreateDefaultSubobject<UCapsuleComponent>("AttackCollision");
	m_pMesh->AttachToComponent(GetRootComponent(), FAttachmentTransformRules::KeepRelativeTransform);
	m_pMesh->SetCollisionEnabled(ECollisionEnabled::NoCollision);
	m_pCollision->AttachToComponent(GetRootComponent(), FAttachmentTransformRules::KeepRelativeTransform);
	m_pCollision->ComponentTags.Add(E_GetCollisionTag());
	m_arCollision.Init(m_pCollision,1);
}

