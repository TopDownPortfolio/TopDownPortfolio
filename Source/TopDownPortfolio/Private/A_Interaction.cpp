#include "A_Interaction.h"

AA_Interaction::AA_Interaction() :
	AActor{}, m_pRoot{}, m_pInteractionReceive{}
{
	PrimaryActorTick.bCanEverTick = false;
}

void AA_Interaction::BeginPlay()
{
	AActor::BeginPlay();
}

void AA_Interaction::OnConstruction(const FTransform& Transform)
{
	AActor::OnConstruction(Transform);
	if (m_pInteractionReceive)
	{
		m_pInteractionReceive->RegisterComponent();
	}
}