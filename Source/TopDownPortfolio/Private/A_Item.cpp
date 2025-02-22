#include "A_Item.h"
#include "Components/StaticMeshComponent.h"
#include "Components/CapsuleComponent.h"

AA_Item::AA_Item() :
	AActor{}, m_pRoot{}, m_pInteractionReceive{}, m_pMeshComponent{}, m_pCollisionComponent{}, nItemID{}, nCount{}
{
	PrimaryActorTick.bCanEverTick = false;
	m_pRoot = CreateDefaultSubobject<USceneComponent>("Root");
	SetRootComponent(m_pRoot);
	m_pMeshComponent = CreateDefaultSubobject< UStaticMeshComponent>("StaticMesh");
	m_pMeshComponent->SetupAttachment(m_pRoot);
	m_pMeshComponent->SetCollisionEnabled(ECollisionEnabled::NoCollision);
	m_pCollisionComponent = CreateDefaultSubobject< UCapsuleComponent>("ItemCollision");
	m_pCollisionComponent->SetupAttachment(m_pRoot);
	m_pInteractionReceive = CreateDefaultSubobject<UC_InteractionReceive_Item>("InteractionReceive");
}

void AA_Item::OnConstruction(const FTransform& Transform)
{
	AActor::OnConstruction(Transform);
	if (m_pInteractionReceive)
	{
		m_pInteractionReceive->RegisterComponent();
	}
}

void AA_Item::BeginPlay()
{
	AActor::BeginPlay();
	m_pInteractionReceive->E_BindCollisionOverlaps(m_pCollisionComponent);
}