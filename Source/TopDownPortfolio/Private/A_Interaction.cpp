#include "A_Interaction.h"

AA_Interaction::AA_Interaction() :
	AActor{}, m_pRoot{}, m_pInteractionReceive{}, m_pActionComponent{}
{
	PrimaryActorTick.bCanEverTick = false;
	m_pRoot = CreateDefaultSubobject<USceneComponent>("Root");
	SetRootComponent(m_pRoot);
}