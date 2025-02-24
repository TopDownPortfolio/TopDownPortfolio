#include "C_InteractionInitiator.h"
#include "A_Interaction.h"

UC_InteractionInitiator::UC_InteractionInitiator() :
	UActorComponent{}, m_arCollsion{}, m_setInteractionReceive{}, m_listReceive{}, m_pFirst{}
{
	PrimaryComponentTick.bCanEverTick = false;
}

void UC_InteractionInitiator::BeginPlay()
{
	UActorComponent::BeginPlay();
}

void UC_InteractionInitiator::E_BeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	AA_Interaction* pInteraction = E_GetInteractionActor(OtherActor);
	if (!pInteraction)
		return;
		E_AddActor(pInteraction);
}

void UC_InteractionInitiator::E_EndOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{
	AA_Interaction* pInteraction = E_GetInteractionActor(OtherActor);
	if (!pInteraction)
		return;
	E_RemoveActor(pInteraction);
}

bool UC_InteractionInitiator::E_AddActor(AA_Interaction* pInteraction)
{
	bool bResult{};
	m_setInteractionReceive.FindOrAdd(pInteraction, &bResult);
	if (!bResult)
	{
		m_listReceive.push_back(pInteraction);
		E_SetFirst();
	}
	return bResult;
}

bool UC_InteractionInitiator::E_RemoveActor(AA_Interaction* pInteraction)
{
	m_setInteractionReceive.Remove(pInteraction);
	m_listReceive.remove(pInteraction);
	E_SetFirst();
	return true;
}

bool UC_InteractionInitiator::E_SetFirst()
{
	std::list < AA_Interaction*>::iterator iter = m_listReceive.begin();
	AA_Interaction* pNewFirst{};
	if (iter != m_listReceive.end())
		pNewFirst = *iter;
	if (m_pFirst == pNewFirst)
		return false;
	UC_InteractionReceive* pReceive{};
	if (m_pFirst)
	{
		m_pFirst->E_GetInteractionReceive(pReceive);
		if (pReceive)
			pReceive->E_Selected(GetOwner(), this, false);
	}
	if (pNewFirst)
	{
		pNewFirst->E_GetInteractionReceive(pReceive);
		if (pReceive)
			pReceive->E_Selected(GetOwner(), this, true);
	}
	m_pFirst = pNewFirst;
	return m_pFirst != nullptr;
}

AA_Interaction* UC_InteractionInitiator::E_GetInteractionActor(AActor* pInteraction)
{
	return Cast< AA_Interaction>(pInteraction);
}

AA_Interaction* UC_InteractionInitiator::E_GetFirst()
{
	return  m_pFirst;
}

bool UC_InteractionInitiator::E_ChangeFirst()
{
	std::list < AA_Interaction*>::iterator iter = m_listReceive.begin();
	AA_Interaction* pFront{};
	if (iter != m_listReceive.end() && *iter != m_pFirst)
	{
		pFront = *iter;
		m_listReceive.pop_front();
		m_listReceive.push_back(pFront);
		E_SetFirst();
	}
	return pFront != nullptr;
}

bool UC_InteractionInitiator::E_Interaction(AA_Interaction*& pInteractedActor)
{
	if (!m_pFirst)
		return false;
	bool bResult{};
	UC_InteractionReceive* pReceive{};
	m_pFirst->E_GetInteractionReceive(pReceive);
	if (pReceive)
		bResult = pReceive->E_Interaction(GetOwner());
	if (bResult)
		pInteractedActor = m_pFirst;
	return bResult;
}

void UC_InteractionInitiator::E_BindCollisionOverlaps(UPrimitiveComponent* pCollision)
{
	if (m_arCollsion.Num() >= E_CollisionSize::E_MaxSize || !pCollision)
		return;
	m_arCollsion.Add(pCollision);
	pCollision->ComponentTags.Add(E_GetCollisionTag());
	pCollision->SetCollisionProfileName(E_GetCollisionProfile());
	pCollision->OnComponentBeginOverlap.AddDynamic(this, &UC_InteractionInitiator::E_BeginOverlap);
	pCollision->OnComponentEndOverlap.AddDynamic(this, &UC_InteractionInitiator::E_EndOverlap);
}
