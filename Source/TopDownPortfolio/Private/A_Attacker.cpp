#include "A_Attacker.h"
#include "A_Character_Base.h"

AA_Attacker::AA_Attacker() :
	AActor{}, m_pRoot{}, m_arCollision{}, m_pOwner{}, m_pAttackMGR{}, m_nAttackIndex{}
{
	PrimaryActorTick.bCanEverTick = false;
	m_pRoot = CreateDefaultSubobject<USceneComponent>("Root");
	SetCanBeDamaged(false);
	SetRootComponent(m_pRoot);
}

void AA_Attacker::E_Destroy(AActor* DestroyedActor)
{
	Destroy();
}

void AA_Attacker::BeginPlay()
{
	AActor::BeginPlay();
}

bool AA_Attacker::E_SetOwner()
{
	APawn* pPawn = GetInstigator();
	if (pPawn)
		m_pOwner = Cast< AA_Character_Base>(pPawn);
	return  m_pOwner != nullptr;
}

bool AA_Attacker::E_SetAttackMGR()
{
	if (E_SetOwner() && !m_pAttackMGR)
	{
		m_pAttackMGR = m_pOwner->E_GetAttackMGR();
	}
	return m_pAttackMGR != nullptr;;
}

bool AA_Attacker::E_CheckOverlap(AActor* pTarget)
{
	AA_Character_Base* pActor = Cast< AA_Character_Base>(pTarget);
	if (!pActor || pActor == m_pOwner || !m_pAttackMGR)
		return false;
	return  m_pAttackMGR->E_IsAlreadyHitted(m_nAttackIndex, pActor) == false;
}

void AA_Attacker::E_BeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	if (E_CheckOverlap(OtherActor))
	{
		E_OverlapEvent(OtherActor);
	}
}

void AA_Attacker::E_OverlapEvent(AActor* pTarget)
{
	m_pAttackMGR->E_AddHitted(m_nAttackIndex, Cast< AA_Character_Base>(pTarget));
}
void AA_Attacker::E_Init(AA_Character_Base* pOwner, FName strSocket)
{
	SetInstigator(pOwner);
	E_SetOwner();
	E_SetAttackMGR();
	m_pOwner->OnDestroyed.AddDynamic(this, &AA_Attacker::E_Destroy);
	AttachToComponent(m_pOwner->GetMesh(), FAttachmentTransformRules::KeepRelativeTransform, strSocket);
	for (UPrimitiveComponent* pCom : m_arCollision)
	{
		pCom->ComponentTags.Add(E_GetCollisionTag());
		pCom->SetCollisionProfileName(E_GetCollisionProfile());
		pCom->OnComponentBeginOverlap.AddDynamic(this, &AA_Attacker::E_BeginOverlap);
	}
	E_OnOfCollisionEnabled(ECollisionEnabled::NoCollision);
}

void AA_Attacker::E_OnAttack()
{
	E_OnOfCollisionEnabled(ECollisionEnabled::QueryOnly);
	E_On();
}

void AA_Attacker::E_OffAttack()
{
	E_OnOfCollisionEnabled(ECollisionEnabled::NoCollision);
	E_Off();
}

void AA_Attacker::E_OnOfCollisionEnabled(ECollisionEnabled::Type eEnable)
{
	for (UPrimitiveComponent* pCom : m_arCollision)
	{
		pCom->SetCollisionEnabled(eEnable);
	}
}

