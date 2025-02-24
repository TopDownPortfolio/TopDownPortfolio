// Copyright Epic Games, Inc. All Rights Reserved.

#include "TopDownPortfolioGameMode.h"
#include "TopDownPortfolioPlayerController.h"
#include "UObject/ConstructorHelpers.h"

ATopDownPortfolioGameMode::ATopDownPortfolioGameMode()
{
	// use our custom PlayerController class
	PlayerControllerClass = ATopDownPortfolioPlayerController::StaticClass();

	// set default pawn class to our Blueprinted character
	static ConstructorHelpers::FClassFinder<APawn> PlayerPawnBPClass(TEXT("/Game/01_Blueprint/Character/Bp_Player"));
	if (PlayerPawnBPClass.Class != nullptr)
	{
		DefaultPawnClass = PlayerPawnBPClass.Class;
	}

	// set default controller to our Blueprinted controller
	static ConstructorHelpers::FClassFinder<APlayerController> PlayerControllerBPClass(TEXT("/Game/TopDown/Blueprints/BP_TopDownPlayerController"));
	if(PlayerControllerBPClass.Class != NULL)
	{
		PlayerControllerClass = PlayerControllerBPClass.Class;
	}
}