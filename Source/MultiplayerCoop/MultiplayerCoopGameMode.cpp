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

void AMultiplayerCoopGameMode::HostLanGame()
{
	GetWorld()->ServerTravel("Game/ThirdPerson/Maps/ThirdPersonMap?Listen"); //launches Map as a listen server
}
void AMultiplayerCoopGameMode::JoinLanGame()
{
	APlayerController *PC =	GetGameInstance()->GetFirstLocalPlayerController();
	if(PC)
	{
		PC->ClientTravel("192.168.1.13", TRAVEL_Absolute);
	}
}
