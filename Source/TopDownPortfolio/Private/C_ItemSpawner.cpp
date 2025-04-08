#include "C_ItemSpawner.h"
#include "A_Interaction_Item.h"

UC_ItemSpawner::UC_ItemSpawner()
{
	PrimaryComponentTick.bCanEverTick = false;
}

void UC_ItemSpawner::EndPlay(const EEndPlayReason::Type EndPlayReason)
{
	UActorComponent::EndPlay(EndPlayReason);
	if (!m_cSpawnItemActor)
		return;
	AActor* pActor = GetOwner();
	for (FS_ItemInstanceData& sData : m_arSpawnItemData  )
	{
		AA_Interaction_Item* pItem = Cast< AA_Interaction_Item>(GetWorld()->SpawnActor(m_cSpawnItemActor));
		if (pItem)
		{
			pItem->SetActorLocation(pActor->GetActorLocation());
			pItem->E_SetItemInstance(sData);
		}
	}
}