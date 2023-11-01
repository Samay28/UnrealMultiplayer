// Copyright Epic Games, Inc. All Rights Reserved.

#include "MultiplayerCoopGameMode.h"
#include "MultiplayerCoopCharacter.h"
#include "UObject/ConstructorHelpers.h"

AMultiplayerCoopGameMode::AMultiplayerCoopGameMode()
{
	// set default pawn class to our Blueprinted character
	static ConstructorHelpers::FClassFinder<APawn> PlayerPawnBPClass(TEXT("/Game/ThirdPerson/Blueprints/BP_ThirdPersonCharacter"));
	if (PlayerPawnBPClass.Class != NULL)
	{
		DefaultPawnClass = PlayerPawnBPClass.Class;
	}
}
