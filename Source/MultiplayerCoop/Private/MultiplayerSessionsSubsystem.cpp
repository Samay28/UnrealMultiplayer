// Fill out your copyright notice in the Description page of Project Settings.

#include "MultiplayerSessionsSubsystem.h"

void PrintString(const FString &str)
{
    if (GEngine)
    {
        GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Cyan, str);
    }
}
UMultiplayerSessionsSubsystem::UMultiplayerSessionsSubsystem()
{
    PrintString("Constructor");
}

void UMultiplayerSessionsSubsystem::Initialize(FSubsystemCollectionBase &Collection)
{
     PrintString("Initialiaze");
}
void UMultiplayerSessionsSubsystem::Deinitialize()
{
    UE_LOG(LogTemp, Warning, TEXT("hahahahaha"));
}