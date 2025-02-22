#include "C_InteractionReceive.h"

UC_InteractionReceive::UC_InteractionReceive() : 
	UActorComponent{}, m_arCollsion{}, m_bDetectTogle{}, m_bDetected{}, m_bAutoBeginInteraction{}, m_bAutoEndInteraction{}
{
	PrimaryComponentTick.bCanEverTick = false;
	m_bAutoBeginInteraction = false;
	m_arCollsion.Reserve(E_CollisionSize::E_MaxSize);
}

void UC_InteractionReceive::E_OnOffCollisions(bool bOnOff)
{
	if (m_arCollsion.IsEmpty())
		return;
	ECollisionEnabled::Type eCollisionEnabled = ECollisionEnabled::NoCollision;
	if (bOnOff)
		eCollisionEnabled = ECollisionEnabled::QueryOnly;
	bool bBreak{};
	UPrimitiveComponent* pCollision{};
	int nArSize = m_arCollsion.Num();
	for (int i = 0; i < nArSize && !bBreak; i++)
	{
		pCollision = m_arCollsion[i];
		bBreak = pCollision->GetCollisionEnabled() == eCollisionEnabled;
		pCollision->SetCollisionEnabled(eCollisionEnabled);
	}
}

void UC_InteractionReceive::E_BindCollisionOverlaps(UPrimitiveComponent* pCollision)
{
	if (m_arCollsion.Num() >= E_CollisionSize::E_MaxSize)
		return;
	m_arCollsion.Add(pCollision);
	pCollision->ComponentTags.Add(E_GetCollisionTag());
	pCollision->SetCollisionProfileName(E_GetCollisionProfile());
	pCollision->OnComponentBeginOverlap.AddDynamic(this, &UC_InteractionReceive::E_BeginOverlap);
	pCollision->OnComponentEndOverlap.AddDynamic(this, &UC_InteractionReceive::E_EndOverlap);
}

void UC_InteractionReceive::E_BeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	if (m_bDetectTogle && !m_bDetected)
	{
		m_bDetected = true;
		E_BeginEvent_Detect_Implementation(OverlappedComponent, OtherActor, OtherComp, OtherBodyIndex, bFromSweep, SweepResult);
	}
	if (m_bAutoBeginInteraction)
	{
		E_BeginEvent_Interaction_Implementation(OtherActor, OtherComp);
	}
}

void UC_InteractionReceive::E_EndOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{
	if (m_bDetectTogle)
	{
		m_bDetected = false;
		E_EndEvent_Detect_Implementation(OverlappedComponent, OtherActor, OtherComp, OtherBodyIndex);
	}
	if (m_bAutoEndInteraction)
	{
		E_EndEvent_Interaction_Implementation(OtherActor, OtherComp);
	}
}

bool UC_InteractionReceive::E_BeginInteractionEvent(AActor* pSrc, UActorComponent* pManageCompo)
{
	if (m_bAutoBeginInteraction)
		return false;
	return E_BeginEvent_Interaction_Implementation(pSrc, pManageCompo);
}

bool UC_InteractionReceive::E_EndInteractionEvent(AActor* pSrc, UActorComponent* pManageCompo)
{
	if (m_bAutoEndInteraction)
		return false;
	return E_EndEvent_Interaction_Implementation(pSrc, pManageCompo);
}