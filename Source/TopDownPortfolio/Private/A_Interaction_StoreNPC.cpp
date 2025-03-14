#include "A_Interaction_StoreNPC.h"
#include "Components/CapsuleComponent.h"
#include "Components/SkeletalMeshComponent.h"
#include "C_InteractionReceive_Store.h"
#include "C_Store.h"

AA_Interaction_StoreNPC::AA_Interaction_StoreNPC() : 
	AA_Interaction{}, m_pInteractionReceiveStore{}, m_pStore{}, m_pCollisionComponent{}, m_pNPCMesh{}
{
	m_pInteractionReceiveStore = CreateDefaultSubobject<UC_InteractionReceive_Store>("Interaction");
	m_pStore = CreateDefaultSubobject<UC_Store>("Store");
	m_pCollisionComponent = CreateDefaultSubobject< UCapsuleComponent>("Collision");
	m_pCollisionComponent->SetupAttachment(m_pRoot);
	m_pNPCMesh = CreateOptionalDefaultSubobject<USkeletalMeshComponent>("Npc");
	m_pNPCMesh->SetupAttachment(m_pRoot);
}

void AA_Interaction_StoreNPC::BeginPlay()
{
	m_pActionComponent = m_pStore;
	m_pInteractionReceive = m_pInteractionReceiveStore;
	AA_Interaction::BeginPlay();
	m_pInteractionReceiveStore->E_BindCollisionOverlaps(m_pCollisionComponent);
}

UC_Store* AA_Interaction_StoreNPC::E_GetStoreComponent()
{
	return m_pStore;
}

void AA_Interaction_StoreNPC::OnConstruction(const FTransform& Transform)
{
	m_pActionComponent = m_pStore;
	m_pInteractionReceive = m_pInteractionReceiveStore;
	AA_Interaction::OnConstruction(Transform);
	if (m_pInteractionReceiveStore)
		m_pInteractionReceiveStore->RegisterComponent();
	if (m_pStore)
		m_pStore->RegisterComponent();
}