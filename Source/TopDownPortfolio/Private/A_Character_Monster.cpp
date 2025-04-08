#include "A_Character_Monster.h"
#include "C_AIActionMGR.h"
#include "Components/CapsuleComponent.h"
#include "Components/SkeletalMeshComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "C_StatusMGR.h"
#include "C_ItemSpawner.h"


AA_Character_Monster::AA_Character_Monster() :
	AA_Character_Base{}, m_pAIAction{}
{
	m_pDamageCollision->SetupAttachment(GetRootComponent());
	m_pAIAction = CreateDefaultSubobject<UC_AIActionMGR>("AIActionMGR");
	m_pStateMGR->E_Init(FE_CharacterType::E_Monster);
	m_pItemSpawn = CreateDefaultSubobject<UC_ItemSpawner>("ItemSpawn");
}

void AA_Character_Monster::OnConstruction(const FTransform& Transform)
{
	AA_Character_Base::OnConstruction(Transform);
	E_RegisterComponent(m_pAIAction);
	E_RegisterComponent(m_pItemSpawn);
}
void AA_Character_Monster::E_Dead()
{
	Destroy(true);
}

bool AA_Character_Monster::E_Defend(float DamageAmount, FDamageEvent const& DamageEvent, AController* EventInstigator, AA_Character_Base* DamageCauser)
{
	bool bResult = AA_Character_Base::E_Defend(DamageAmount, DamageEvent, EventInstigator, DamageCauser);
	float fHp = m_pStatusMGR->E_GetStatus_Current(FE_StatusID::E_HP);
	if (fHp > 0)
		return bResult;
	FTimerHandle sHandle{};
	GetWorldTimerManager().SetTimer(sHandle, this, &AA_Character_Monster::E_Dead, 1.0f, false, 3.0f);
	USkeletalMeshComponent* pMesh = GetMesh();
	if (pMesh)
	{
		pMesh->SetAllBodiesSimulatePhysics(true);
		pMesh->SetCollisionProfileName("Ragdoll");
	}
	GetCapsuleComponent()->SetCollisionEnabled(ECollisionEnabled::NoCollision);
	return bResult;
}
