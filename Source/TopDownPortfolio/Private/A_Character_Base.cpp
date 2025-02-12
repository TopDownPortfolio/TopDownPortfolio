#include "A_Character_Base.h"
#include "Engine/DamageEvents.h"
#include "Components/CapsuleComponent.h"
#include "Kismet/GameplayStatics.h"
#include "Perception/AISenseConfig_Damage.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "C_BuffMGR.h"
#include "C_StatusMGR.h"
#include "C_AttackMGR.h"
#include "C_MontageMGR.h"

AA_Character_Base::AA_Character_Base() :
	ACharacter{}, m_pMontageMGR{}, m_pStatusMGR{}, m_pAttackMGR{}, m_pDamageCollision{}, m_pBuffMGR{}, m_eState{}, m_arHideBone {}
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
	E_AddState(FE_StateType::E_IsTravel);
	E_HideSocket();
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

void AA_Character_Base::E_AddState(FE_StateType eEnum)
{
	m_eState |= (uint8)eEnum;
}

void AA_Character_Base::E_SubState(FE_StateType eEnum)
{
	if (E_CheckState(eEnum))
		m_eState ^= (uint8)eEnum;
}


bool AA_Character_Base::ShouldTakeDamage(float Damage, FDamageEvent const& DamageEvent, AController* EventInstigator, AActor* DamageCauser) const
{	
	bool bResult = ACharacter::ShouldTakeDamage(Damage, DamageEvent, EventInstigator, DamageCauser);

	return bResult;
}


void AA_Character_Base::E_Action_Implementation(FE_SkillID eID)
{
	
}

void AA_Character_Base::E_Attack(AA_Character_Base* pTarget)
{
	float fDamage = E_GetStatusMGR()->E_GetStatus_Current(FE_StatusID::E_ATTACK);
	FDamageEvent fDamageEvent{};
	pTarget->E_Defend(fDamage, fDamageEvent, GetController(), this);
}

void AA_Character_Base::E_Defend(float DamageAmount, FDamageEvent const& DamageEvent, AController* EventInstigator, AA_Character_Base* DamageCauser)
{
	if (!CanBeDamaged())
		return;

	E_SubState(FE_StateType::E_IsTravel);
	float fDamage = DamageAmount;
	float fDefend = E_GetStatusMGR()->E_GetStatus_Current(FE_StatusID::E_DEFEND);
	if (fDefend > 0.0f)
		fDamage -= fDefend;
	if (fDamage < 0.0f)
		fDamage = 0.0f;
	else
	{
		float fHP = E_GetStatusMGR()->E_GetStatus_Current(FE_StatusID::E_HP);
		if (fHP - fDamage < 0.0f)
			fDamage = fHP;
		E_GetStatusMGR()->E_AddStatus_Current(FE_StatusID::E_HP, -fDamage);
	}

	//TakeDamage(fDamage, DamageEvent, EventInstigator, DamageCauser);
	UGameplayStatics::ApplyDamage(this, fDamage, EventInstigator, DamageCauser, UDamageType::StaticClass());
	UAISense_Damage::ReportDamageEvent(GetWorld(), this, DamageCauser, fDamage, GetActorLocation(), FVector::Zero());
}
