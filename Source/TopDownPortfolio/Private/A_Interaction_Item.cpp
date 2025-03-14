#include "A_Interaction_Item.h"
#include "Components/StaticMeshComponent.h"
#include "Components/CapsuleComponent.h"
#include "C_InteractionReceive_Item.h"
#include "BFL_ItemLibrary.h"

AA_Interaction_Item::AA_Interaction_Item() :
	AA_Interaction{}, m_pMeshComponent{}, m_pCollisionComponent{}, m_sItemInstanceData{}
{
	PrimaryActorTick.bCanEverTick = false;
	m_pMeshComponent = CreateDefaultSubobject< UStaticMeshComponent>("StaticMesh");
	m_pMeshComponent->SetupAttachment(m_pRoot);
	m_pMeshComponent->SetCollisionEnabled(ECollisionEnabled::NoCollision);
	m_pCollisionComponent = CreateDefaultSubobject< UCapsuleComponent>("ItemCollision");
	m_pCollisionComponent->SetupAttachment(m_pRoot);
	m_pInteractionReceiveItem = CreateDefaultSubobject<UC_InteractionReceive_Item>("InteractionReceive");
	m_sItemInstanceData.nItemCount = 1;
}

void AA_Interaction_Item::OnConstruction(const FTransform& Transform)
{
	m_pInteractionReceive = m_pInteractionReceiveItem;
	AA_Interaction::OnConstruction(Transform);
	if (m_pInteractionReceiveItem)
	{
		m_pInteractionReceiveItem->RegisterComponent();
	}
}

void AA_Interaction_Item::BeginPlay()
{
	m_pInteractionReceive = m_pInteractionReceiveItem;
	AA_Interaction::BeginPlay();
	m_pInteractionReceiveItem->E_BindCollisionOverlaps(m_pCollisionComponent);

	//UStaticMesh* pMesh{}; // = m_pMeshComponent->GetStaticMesh();
	//UBFL_ItemLibrary::E_GetItemStaticMesh(this, m_sItemInstanceData.eItemType, m_sItemInstanceData.nItemID, pMesh);
	//if (m_pMeshComponent && pMesh)
	//{
	//	m_pMeshComponent->SetStaticMesh(pMesh);
	//} MESH가 너무 작게 반영되서 기본 Mesh 퉁 치는 걸로 변경 에정
}

void AA_Interaction_Item::E_SetItemInstance(FS_ItemInstanceData& nItemInstance)
{
	nItemInstance.nItemID = m_sItemInstanceData.nItemID;
	nItemInstance.eItemType = m_sItemInstanceData.eItemType;
	nItemInstance.nItemCount= m_sItemInstanceData.nItemCount;
}
