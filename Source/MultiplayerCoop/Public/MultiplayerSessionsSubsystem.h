// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Subsystems/GameInstanceSubsystem.h"
#include "Interfaces/OnlineSessionInterface.h"
#include "OnlineSessionSettings.h"  //for creating sessions
#include "MultiplayerSessionsSubsystem.generated.h"

/**
 *
 */
UCLASS()
class MULTIPLAYERCOOP_API UMultiplayerSessionsSubsystem : public UGameInstanceSubsystem
{
	GENERATED_BODY()

public:
	UMultiplayerSessionsSubsystem();

	void Initialize(FSubsystemCollectionBase &Collection) override; // copy paste from docs
	void Deinitialize() override;

	IOnlineSessionPtr SessionInterface;

	UFUNCTION(BlueprintCallable)
	void CreateServer(FString ServerName);

	UFUNCTION(BlueprintCallable)
	void FindServer(FString ServerName);

	void OnCreateSessionComplete(FName SessionName, bool WasSuccessful); //for delegates
	void OnDestroySessionComplete(FName SessionName, bool WasSuccessful);

	bool CreateServerAfterDestroy;
	FString DestroyServerName;
	FString ServerNameToFind;

	TSharedPtr<FOnlineSessionSearch> SessionSearch;
	void OnFindSessionsComplete(bool WasSuccessful);
};
