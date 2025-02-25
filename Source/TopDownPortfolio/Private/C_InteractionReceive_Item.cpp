#include "C_InteractionReceive_Item.h"
#include "A_PlayerController.h"
#include "A_Interaction_Item.h"
#include "C_Inventory.h"
#include "Components/StaticMeshComponent.h"

UC_InteractionReceive_Item::UC_InteractionReceive_Item() : 
	UC_InteractionReceive{}, m_pStaticMesh{}, m_pDetected{}, m_pSelected{}, m_pItem{}
{
	m_bSelectableTogle = true;
	m_bDetectTogle = true;
}

void UC_InteractionReceive_Item::E_SetMaterialInterface(UMaterialInterface* pMaterial)
{
	if (m_pStaticMesh)
		m_pStaticMesh->SetOverlayMaterial(pMaterial);
}

void UC_InteractionReceive_Item::BeginPlay()
{
	UC_InteractionReceive::BeginPlay();
	m_pItem = Cast<AA_Interaction_Item>(GetOwner());
	if (!m_pItem)
	{
		DestroyComponent();
		return;
	}
	m_pStaticMesh = m_pItem->E_GetStaticMeshComponent();
}

bool UC_InteractionReceive_Item::E_BeginEvent_Detect_Implementation(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	if (!m_bSelected)
		E_SetMaterialInterface(m_pDetected);
	return !m_bSelected;
}

bool UC_InteractionReceive_Item::E_EndEvent_Detect_Implementation(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{
	E_SetMaterialInterface(nullptr);
	return true;
}

bool UC_InteractionReceive_Item::E_InteractionEvent_Implementation(AActor* pInitiator)
{
	APawn* pPlayer = Cast < APawn>(pInitiator);
	if (!pPlayer)
		return false;
	AA_PlayerController* pController = Cast< AA_PlayerController>(pPlayer->GetController());
	UC_Inventory* pInventroy = pController->E_GetInventory();
	FS_ItemInstanceData sInstanceData{};
	m_pItem->E_SetItemInstance(sInstanceData);
	return pInventroy->E_PushItem(&sInstanceData);
}

bool UC_InteractionReceive_Item::E_SelectedOnEvent_Implementation(AActor* pInitiator, UActorComponent* pInteractionCompo)
{
	E_SetMaterialInterface(m_pSelected);
	return true;
}

bool UC_InteractionReceive_Item::E_SelectedOffEvent_Implementation(AActor* pInitiator, UActorComponent* pInteractionCompo)
{
	UMaterialInterface* pNext{};
	if (m_bDetected)
		pNext = m_pDetected;
	E_SetMaterialInterface(pNext);
	return m_bDetected;
}

bool UC_InteractionReceive_Item::E_InteractionEnd_Implementation(AActor* pInitiator)
{
	if (m_bInteractionResult)
	{
		m_pItem->Destroy();
	}
	return m_bInteractionResult;
}
