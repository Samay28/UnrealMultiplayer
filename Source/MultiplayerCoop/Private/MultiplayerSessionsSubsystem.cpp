// Fill out your copyright notice in the Description page of Project Settings.

#include "MultiplayerSessionsSubsystem.h"
#include "OnlineSubsystem.h"
void PrintString(const FString &str)
{
    if (GEngine)
    {
        GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Cyan, str);
    }
}
UMultiplayerSessionsSubsystem::UMultiplayerSessionsSubsystem()
{
    CreateServerAfterDestroy = false;
    DestroyServerName = "";
    ServerNameToFind = "";
}

void UMultiplayerSessionsSubsystem::Initialize(FSubsystemCollectionBase &Collection)
{
    IOnlineSubsystem *OnlineSubsystem = IOnlineSubsystem::Get();
    if (OnlineSubsystem)
    {
        FString SubsystemName = OnlineSubsystem->GetSubsystemName().ToString();
        PrintString(SubsystemName);

        SessionInterface = OnlineSubsystem->GetSessionInterface();

        if (SessionInterface.IsValid())
        {
            SessionInterface->OnCreateSessionCompleteDelegates.AddUObject(this, &UMultiplayerSessionsSubsystem::OnCreateSessionComplete); // binding
            SessionInterface->OnDestroySessionCompleteDelegates.AddUObject(this, &UMultiplayerSessionsSubsystem::OnDestroySessionComplete);
            SessionInterface->OnFindSessionsCompleteDelegates.AddUObject(this, &UMultiplayerSessionsSubsystem::OnFindSessionsComplete);
        }
    }
}
void UMultiplayerSessionsSubsystem::Deinitialize()
{
}

void UMultiplayerSessionsSubsystem::CreateServer(FString ServerName)
{

    // if (ServerName.IsEmpty())
    // {
    //     PrintString("Server Name Cannot Be Empty");
    //     return;
    // }
    FName MySessionName = FName("Co-op Adventure Session Name");
    FNamedOnlineSession *ExistingSession = SessionInterface->GetNamedSession(MySessionName); // checking if session of same name exists

    if (ExistingSession)
    {
        FString msg = FString::Printf(TEXT("Destroying session"));
        PrintString(msg);
        CreateServerAfterDestroy = true;
        DestroyServerName = ServerName;
        SessionInterface->DestroySession(MySessionName); // destroy if it exists
        return;
    }

    FOnlineSessionSettings SessionSettings;

    SessionSettings.bAllowJoinInProgress = true;
    SessionSettings.bIsDedicated = false;
    SessionSettings.bShouldAdvertise = true;
    SessionSettings.NumPublicConnections = 2;
    SessionSettings.bUseLobbiesIfAvailable = true;
    SessionSettings.bUsesPresence = true;
    SessionSettings.bAllowJoinViaPresence = true;
    bool IsLan = false;

    if (IOnlineSubsystem::Get()->GetSubsystemName() == "NULL")
    {
        IsLan = true;
    }
    SessionSettings.bIsLANMatch = IsLan;

    SessionSettings.Set(FName("SERVER_NAME"), ServerName, EOnlineDataAdvertisementType::ViaOnlineServiceAndPing);  //storing server name in session settings before creating session
    SessionInterface->CreateSession(0, MySessionName, SessionSettings);
}

void UMultiplayerSessionsSubsystem::FindServer(FString ServerName)
{
    PrintString("Joined Server");

    if (ServerName.IsEmpty())
    {
        PrintString("empty");
        return;
    }

    SessionSearch = MakeShareable(new FOnlineSessionSearch()); // as it is a pointter we create a object
    bool IsLan = false;
    if (IOnlineSubsystem::Get()->GetSubsystemName() == "NULL")
    {
        IsLan = true;
    }
    SessionSearch->bIsLanQuery = IsLan;
    SessionSearch->MaxSearchResults = 9999;
    SessionSearch->QuerySettings.Set(SEARCH_PRESENCE, true, EOnlineComparisonOp::Equals); // search presence options to be true

    ServerNameToFind = ServerName;
    SessionInterface->FindSessions(0, SessionSearch.ToSharedRef());
}

void UMultiplayerSessionsSubsystem::OnCreateSessionComplete(FName SessionName, bool WasSuccessful)
{
    PrintString(FString::Printf(TEXT("%d"), WasSuccessful));

    if (WasSuccessful)
    {
        GetWorld()->ServerTravel("/Game/ThirdPerson/Maps/ThirdPersonMap?listen"); // launch map as a listen server
    }
}

void UMultiplayerSessionsSubsystem::OnDestroySessionComplete(FName SessionName, bool WasSuccessful)
{
    PrintString("Session destroyed delegate was fired");
    if (CreateServerAfterDestroy)
    {
        CreateServerAfterDestroy = false;
        CreateServer(DestroyServerName);
    }
}

void UMultiplayerSessionsSubsystem::OnFindSessionsComplete(bool WasSuccessful)
{
    if (WasSuccessful)
    {   
        if(ServerNameToFind.IsEmpty()) return;
        
        TArray<FOnlineSessionSearchResult> Results = SessionSearch->SearchResults;
        if (Results.Num() > 0)
        {
            FString msg = FString::Printf(TEXT("%d sessions found"), Results.Num());
            PrintString(msg);

            for (FOnlineSessionSearchResult Result : Results) //looping thru available servers
            {
                if (Result.IsValid())
                {
                    FString ServerName = "No-Name";
                    Result.Session.SessionSettings.Get(FName("SERVER_NAME"), ServerName);

                    FString msg2 = FString::Printf(TEXT("ServerName: %s"), *ServerName);
                    PrintString(msg2);
                }
            }
        }
        else
        {
            PrintString("noo sessionss");
        }
    }
    else
        return;
}
