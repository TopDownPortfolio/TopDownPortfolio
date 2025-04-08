#include "A_Character_Base.h"
#include "Engine/DamageEvents.h"
#include "Components/CapsuleComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "C_BuffMGR.h"
#include "C_StatusMGR.h"

AA_Character_Base::AA_Character_Base() :
	ACharacter{}, m_pMontageMGR{}, m_pStatusMGR{}, m_pAttackMGR{}, m_pDamageCollision{}, m_pBuffMGR{}, m_arHideBone{}, m_pStateMGR{}, m_pDefendMGR{}
{
	PrimaryActorTick.bCanEverTick = true;
	bReplicates = true;

	m_pMontageMGR = CreateDefaultSubobject<UC_MontageMGR>("MontageMGR");
	m_pStatusMGR = CreateDefaultSubobject<UC_StatusMGR>("StatusMGR");
	m_pAttackMGR = CreateDefaultSubobject<UC_AttackMGR>("AttackMGR");
	m_pDamageCollision = CreateDefaultSubobject<UCapsuleComponent>("DamageCollision");
	m_pDamageCollision->SetupAttachment(GetRootComponent());
	m_pDamageCollision->SetCollisionProfileName(E_GetDamageCollisionProfile());

	m_pBuffMGR = CreateDefaultSubobject<UC_BuffMGR>("BuffMGR");
	m_pStateMGR= CreateDefaultSubobject<UC_StateMGR>("StateMGR");
	m_pDefendMGR = CreateDefaultSubobject<UC_DefendMGR>("DefendMGR");
}

void AA_Character_Base::OnConstruction(const FTransform& Transform)
{
	ACharacter::OnConstruction(Transform);
	E_RegisterComponent(m_pMontageMGR);
	E_RegisterComponent(m_pStatusMGR);
	E_RegisterComponent(m_pAttackMGR);
	E_RegisterComponent(m_pBuffMGR);
}

void AA_Character_Base::BeginPlay()
{
	Super::BeginPlay();
	E_HideSocket();
	E_GetDefendMGR()->On_StartDamage.AddDynamic(this, &AA_Character_Base::E_SwitchMode);
}

void AA_Character_Base::E_RegisterComponent(UActorComponent* pComponent)
{
	if (pComponent)
		pComponent->RegisterComponent();
}

void AA_Character_Base::E_HideSocket()
{
	USkeletalMeshComponent* pMesh = GetMesh();
	for (FName & name : m_arHideBone)
	{
		pMesh->HideBoneByName(name, EPhysBodyOp::PBO_None);
	}
}

void AA_Character_Base::E_SwitchMode()
{
	m_pStateMGR->E_SubState(FE_StateFlag::E_IsTravel);
	m_pStateMGR->E_AddState(FE_StateFlag::E_IsHitted);
}

bool AA_Character_Base::E_Attack(AA_Character_Base* pTarget)
{
	FE_Affiliation eAffiliation = m_pStateMGR->E_GetAffiliation(pTarget);
	if (eAffiliation != FE_Affiliation::E_Enemy)
		return false;
	float fDamage = E_GetStatusMGR()->E_GetStatus_Current(FE_StatusID::E_ATTACK);
	FDamageEvent fDamageEvent{};
	fDamageEvent.DamageTypeClass = E_GetAttackMGR()->E_GetDamageType();
	return 	pTarget->E_Defend(fDamage, fDamageEvent, GetController(), this);
}

bool AA_Character_Base::E_Defend(float DamageAmount, FDamageEvent const& DamageEvent, AController* EventInstigator, AA_Character_Base* DamageCauser)
{
	if (!E_GetDefendMGR())
		return false;
	return E_GetDefendMGR()->E_Defend(DamageAmount, DamageEvent, EventInstigator, DamageCauser);
}
