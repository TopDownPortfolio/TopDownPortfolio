#include "C_InteractionReceive_Item.h"
#include "A_Character_Player.h"
#include "A_Interaction_Item.h"
#include "Components/StaticMeshComponent.h"

UC_InteractionReceive_Item::UC_InteractionReceive_Item() : 
	UC_InteractionReceive{}, m_pStaticMesh{}, m_pDetected{}, m_pSelected{}
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
	AA_Interaction_Item* pItem = Cast<AA_Interaction_Item>(GetOwner());
	if (!pItem)
	{
		DestroyComponent();
		return;
	}
	m_pStaticMesh = pItem->E_GetStaticMeshComponent();
}

bool UC_InteractionReceive_Item::E_BeginEvent_Detect_Implementation(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	if (!m_bSelected)
		E_SetMaterialInterface(m_pDetected);
	return true;
}

bool UC_InteractionReceive_Item::E_EndEvent_Detect_Implementation(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{
	E_SetMaterialInterface(nullptr);
	return false;
}

bool UC_InteractionReceive_Item::E_InteractionEvent_Implementation(AActor* pInitiator)
{
	AA_Character_Player* pPlayer = Cast < AA_Character_Player>(pInitiator);
	if (!pPlayer)
		return false;
	pPlayer->E_Test(GetOwner());
	return true;
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
	return true;
}
