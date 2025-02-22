#include "C_InteractionReceive_Item.h"
#include "A_Character_Player.h"

UC_InteractionReceive_Item::UC_InteractionReceive_Item()
{
}

bool UC_InteractionReceive_Item::E_BeginEvent_Detect_Implementation(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	return false;
}

bool UC_InteractionReceive_Item::E_EndEvent_Detect_Implementation(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{
	return false;
}

bool UC_InteractionReceive_Item::E_BeginEvent_Interaction_Implementation(AActor* pSrc, UActorComponent* pManageCompo)
{
	AA_Character_Player* pPlayer = Cast < AA_Character_Player>(pSrc);
	if (!pPlayer)
		return false;
	pPlayer->E_Test(GetOwner());
	return true;
}