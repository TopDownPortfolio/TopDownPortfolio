#include "A_Interaction_Item.h"
#include "Components/StaticMeshComponent.h"
#include "Components/CapsuleComponent.h"
#include "C_InteractionReceive_Item.h"

AA_Interaction_Item::AA_Interaction_Item() :
	AA_Interaction{}, m_pMeshComponent{}, m_pCollisionComponent{}, m_nItemID{}, m_nCount{}
{
	PrimaryActorTick.bCanEverTick = false;
	m_pRoot = CreateDefaultSubobject<USceneComponent>("Root");
	SetRootComponent(m_pRoot);
	m_pMeshComponent = CreateDefaultSubobject< UStaticMeshComponent>("StaticMesh");
	m_pMeshComponent->SetupAttachment(m_pRoot);
	m_pMeshComponent->SetCollisionEnabled(ECollisionEnabled::NoCollision);
	m_pCollisionComponent = CreateDefaultSubobject< UCapsuleComponent>("ItemCollision");
	m_pCollisionComponent->SetupAttachment(m_pRoot);
	m_pInteractionReceiveItem = CreateDefaultSubobject<UC_InteractionReceive_Item>("InteractionReceive");
	m_nCount = 1;
}

void AA_Interaction_Item::OnConstruction(const FTransform& Transform)
{
	m_pInteractionReceive = m_pInteractionReceiveItem;
	AA_Interaction::OnConstruction(Transform);
}

void AA_Interaction_Item::BeginPlay()
{
	m_pInteractionReceive = m_pInteractionReceiveItem;
	AA_Interaction::BeginPlay();
	m_pInteractionReceiveItem->E_BindCollisionOverlaps(m_pCollisionComponent);
}