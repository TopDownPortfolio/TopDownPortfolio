#include "G_GameModeBase.h"
#include "A_PlayerController.h"
#include "A_Character_Player.h"
#include "UObject/ConstructorHelpers.h"
#include "C_ItemDataTable.h"

AG_GameModeBase::AG_GameModeBase() : 
	AGameModeBase{}
{
	// Script / Engine.Blueprint'/Game/02_Data/Player/Berserker/Bp_Berserker.Bp_Berserker'
	static ConstructorHelpers::FClassFinder<APawn> PlayerPawnBPClass(TEXT("/Game/02_Data/Player/Berserker/Bp_Berserker"));
	if (PlayerPawnBPClass.Class != nullptr)
	{
		DefaultPawnClass = PlayerPawnBPClass.Class;
	}
	static ConstructorHelpers::FClassFinder<APlayerController> PlayerControllerBPClass(TEXT("/Game/01_Blueprint/Player/BP_TopDownPlayerController"));
	if (PlayerControllerBPClass.Class != NULL)
	{
		PlayerControllerClass = PlayerControllerBPClass.Class;
	}

	if(!PlayerControllerClass)
		PlayerControllerClass = AA_PlayerController::StaticClass();
	if(!DefaultPawnClass)
		DefaultPawnClass = AA_Character_Player::StaticClass();
	m_pItemDataTable = CreateDefaultSubobject<UC_ItemDataTable>("ItemDataTableComponent");
}

void AG_GameModeBase::OnConstruction(const FTransform& Transform)
{
	AGameModeBase::OnConstruction(Transform);
	if (m_pItemDataTable)
		m_pItemDataTable->RegisterComponent();
}

void AG_GameModeBase::StartPlay()
{
	AGameModeBase::StartPlay();
}
