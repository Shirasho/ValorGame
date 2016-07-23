// Copyright Shirasho Media 2016. All rights reserved.

#include "ValorGame.h"
#include "ValorGameSession.h"

#include "ValorPlayerController.h"
#include "Online/ValorOnlineSettings.h"

AValorGameSession::AValorGameSession(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer)
{
	if (!HasAnyFlags(RF_ClassDefaultObject))
	{
		OnCreateSessionCompleteDelegate = FOnCreateSessionCompleteDelegate::CreateUObject(this, &AValorGameSession::OnCreateSessionComplete);
		OnDestroySessionCompleteDelegate = FOnDestroySessionCompleteDelegate::CreateUObject(this, &AValorGameSession::OnDestroySessionComplete);

		OnFindSessionsCompleteDelegate = FOnFindSessionsCompleteDelegate::CreateUObject(this, &AValorGameSession::OnFindSessionsComplete);
		OnJoinSessionCompleteDelegate = FOnJoinSessionCompleteDelegate::CreateUObject(this, &AValorGameSession::OnJoinSessionComplete);

		OnStartSessionCompleteDelegate = FOnStartSessionCompleteDelegate::CreateUObject(this, &AValorGameSession::OnStartOnlineGameComplete);
	}
}

void AValorGameSession::ResetBestSessionVars()
{
	CurrentSessionParams.BestSessionIdx = -1;
}

void AValorGameSession::ChooseBestSession()
{
	for (int32 SessionIndex = CurrentSessionParams.BestSessionIdx + 1; SessionIndex < SearchSettings->SearchResults.Num(); ++SessionIndex)
	{
		CurrentSessionParams.BestSessionIdx = SessionIndex;
		return;
	}

	CurrentSessionParams.BestSessionIdx = -1;
}

void AValorGameSession::StartMatchmaking()
{
	ResetBestSessionVars();
	ContinueMatchmaking();
}

void AValorGameSession::ContinueMatchmaking()
{
	ChooseBestSession();
	if (CurrentSessionParams.BestSessionIdx >= 0 && CurrentSessionParams.BestSessionIdx < SearchSettings->SearchResults.Num())
	{
		const IOnlineSubsystem* OnlineSubsystem = IOnlineSubsystem::Get();
		if (OnlineSubsystem)
		{
			IOnlineSessionPtr SessionInterface = OnlineSubsystem->GetSessionInterface();
			if (SessionInterface.IsValid() && CurrentSessionParams.UserId.IsValid())
			{
				OnJoinSessionCompleteDelegateHandle = SessionInterface->AddOnJoinSessionCompleteDelegate_Handle(OnJoinSessionCompleteDelegate);
				SessionInterface->JoinSession(*CurrentSessionParams.UserId, CurrentSessionParams.SessionName, SearchSettings->SearchResults[CurrentSessionParams.BestSessionIdx]);
			}
		}
	}
	else
	{
		OnNoMatchesAvailable();
	}
}

void AValorGameSession::FindSessions(TSharedPtr<const FUniqueNetId> UserId, FName SessionName, bool bIsLan, bool bIsPresence)
{
	const IOnlineSubsystem* OnlineSubsystem = IOnlineSubsystem::Get();
	if (OnlineSubsystem)
	{
		CurrentSessionParams.SessionName = SessionName;
		CurrentSessionParams.bIsLan = bIsLan;
		CurrentSessionParams.bIsPresence = bIsPresence;
		CurrentSessionParams.UserId = UserId;

		IOnlineSessionPtr SessionInterface = OnlineSubsystem->GetSessionInterface();
		if (SessionInterface.IsValid() && CurrentSessionParams.UserId.IsValid())
		{
			SearchSettings = MakeShareable(new FValorOnlineSearchSettings(bIsLan, bIsPresence));
			SearchSettings->QuerySettings.Set(SEARCH_KEYWORDS, ValorKeywords::CustomMatchKeyword, EOnlineComparisonOp::Equals);

			TSharedRef<FOnlineSessionSearch> SearchSettingsReference = SearchSettings.ToSharedRef();

			OnFindSessionsCompleteDelegateHandle = SessionInterface->AddOnFindSessionsCompleteDelegate_Handle(OnFindSessionsCompleteDelegate);
			SessionInterface->FindSessions(*CurrentSessionParams.UserId, SearchSettingsReference);
		}
	}
	else
	{
		OnFindSessionsComplete(false);
	}
}

bool AValorGameSession::JoinSession(TSharedPtr<const FUniqueNetId> UserId, FName SessionName, int32 SessionIndexInSearchResults)
{
	bool bResult = false;

	if (SessionIndexInSearchResults >= 0 && SessionIndexInSearchResults < SearchSettings->SearchResults.Num())
	{
		bResult = JoinSession(UserId, SessionName, SearchSettings->SearchResults[SessionIndexInSearchResults]);
	}

	return bResult;
}

bool AValorGameSession::JoinSession(TSharedPtr<const FUniqueNetId> UserId, FName SessionName, const FOnlineSessionSearchResult& SearchResult)
{
	bool bResult = false;

	const IOnlineSubsystem* OnlineSubsystem = IOnlineSubsystem::Get();
	if (OnlineSubsystem)
	{
		IOnlineSessionPtr SessionInterface = OnlineSubsystem->GetSessionInterface();
		if (SessionInterface.IsValid() && UserId.IsValid())
		{
			OnJoinSessionCompleteDelegateHandle = SessionInterface->AddOnJoinSessionCompleteDelegate_Handle(OnJoinSessionCompleteDelegate);
			bResult = SessionInterface->JoinSession(*UserId, SessionName, SearchResult);
		}
	}

	return bResult;
}

void AValorGameSession::OnStartOnlineGameComplete(FName SessionName, bool bWasSuccessful)
{
	const IOnlineSubsystem* OnlineSubsystem = IOnlineSubsystem::Get();
	if (OnlineSubsystem)
	{
		IOnlineSessionPtr SessionInterface = OnlineSubsystem->GetSessionInterface();
		if (SessionInterface.IsValid())
		{
			/* Unbind this delegate handle so it is not called again (and can be rebound later). */
			SessionInterface->ClearOnStartSessionCompleteDelegate_Handle(OnStartSessionCompleteDelegateHandle);
		}
	}

	/* If the game successfully started... */
	if (bWasSuccessful)
	{
		/* Tell remote players to start the online game. */
		for (FConstPlayerControllerIterator Iterator = GetWorld()->GetPlayerControllerIterator(); Iterator; ++Iterator)
		{
			AValorPlayerController* PlayerController = Cast<AValorPlayerController>(*Iterator);
			if (PlayerController && !PlayerController->IsLocalPlayerController())
			{
				PlayerController->ClientStartOnlineMatch();
			}
		}
	}
}

void AValorGameSession::OnCreateSessionComplete(FName SessionName, bool bWasSuccessful)
{
	UE_LOG(LogValorServer, Verbose, TEXT("OnCreateSessionComplete - Session '%s' creation status: %d"), *SessionName.ToString(), bWasSuccessful);

	const IOnlineSubsystem* OnlineSubsystem = IOnlineSubsystem::Get();
	if (OnlineSubsystem)
	{
		IOnlineSessionPtr SessionInterface = OnlineSubsystem->GetSessionInterface();
		if (SessionInterface.IsValid())
		{
			/* Unbind the OnCreateSessionCompleteDelegate so it is not triggered again. */
			SessionInterface->ClearOnCreateSessionCompleteDelegate_Handle(OnCreateSessionCompleteDelegateHandle);
		}
	}

	OnCreatePresenceSessionComplete().Broadcast(SessionName, bWasSuccessful);
}

void AValorGameSession::OnDestroySessionComplete(FName SessionName, bool bWasSuccessful)
{
	UE_LOG(LogValorServer, Verbose, TEXT("OnDestroySessionComplete - Session '%s' destruction status: %d"), *SessionName.ToString(), bWasSuccessful);

	const IOnlineSubsystem* OnlineSubsystem = IOnlineSubsystem::Get();
	if (OnlineSubsystem)
	{
		IOnlineSessionPtr SessionInterface = OnlineSubsystem->GetSessionInterface();
		if (SessionInterface.IsValid())
		{
			/* Unbind the OnDestroySessionCompleteDelegate so it is not triggered again. */
			SessionInterface->ClearOnDestroySessionCompleteDelegate_Handle(OnDestroySessionCompleteDelegateHandle);
			HostSettings = nullptr;
		}
	}
}

void AValorGameSession::OnFindSessionsComplete(bool bWasSuccessful)
{
	UE_LOG(LogValorServer, Verbose, TEXT("OnFindSessionsComplete - Found session(s) status: %d"), bWasSuccessful);

	const IOnlineSubsystem* OnlineSubsystem = IOnlineSubsystem::Get();
	if (OnlineSubsystem)
	{
		IOnlineSessionPtr SessionInterface = OnlineSubsystem->GetSessionInterface();
		if (SessionInterface.IsValid())
		{
			SessionInterface->ClearOnFindSessionsCompleteDelegate_Handle(OnFindSessionsCompleteDelegateHandle);

			/* Log the session. */
			if (SearchSettings.IsValid())
			{
				UE_LOG(LogValorServer, Verbose, TEXT("Number of search results: %d"), SearchSettings->SearchResults.Num());
				for (int32 SearchIndex = 0; SearchIndex < SearchSettings->SearchResults.Num(); ++SearchIndex)
				{
					const FOnlineSessionSearchResult& SearchResult = SearchSettings->SearchResults[SearchIndex];
					DumpSession(&SearchResult.Session);
				}
			}
			else
			{
				UE_LOG(LogValorServer, Verbose, TEXT("Number of search results: 0 (invalid search settings)"));
			}

			OnFindSessionsComplete().Broadcast(bWasSuccessful);
		}
	}
}

void AValorGameSession::OnJoinSessionComplete(FName SessionName, EOnJoinSessionCompleteResult::Type Result)
{
	UE_LOG(LogValorServer, Verbose, TEXT("OnJoinSessionComplete - Join session '%s' status: %d"), *SessionName.ToString(), static_cast<int32>(Result));

	const IOnlineSubsystem* OnlineSubystem = IOnlineSubsystem::Get();
	if (OnlineSubystem)
	{
		IOnlineSessionPtr SessionInterface = OnlineSubystem->GetSessionInterface();
		if (SessionInterface.IsValid())
		{
			SessionInterface->ClearOnJoinSessionCompleteDelegate_Handle(OnJoinSessionCompleteDelegateHandle);
		}
	}

	OnJoinSessionComplete().Broadcast(Result);
}

void AValorGameSession::OnNoMatchesAvailable()
{
	UE_LOG(LogValorServer, Verbose, TEXT("Matchmaking complete. No sessions are available."));
	SearchSettings = nullptr;
}

void AValorGameSession::HandleMatchHasStarted()
{
	const IOnlineSubsystem* OnlineSubsystem = IOnlineSubsystem::Get();
	if (OnlineSubsystem)
	{
		IOnlineSessionPtr SessionInterface = OnlineSubsystem->GetSessionInterface();
		if (SessionInterface.IsValid())
		{
			UE_LOG(LogValorServer, Log, TEXT("Starting session %s on server."), *GameSessionName.ToString());

			/* Bind the start session delegate that fires once the session has successfully started. */
			OnStartSessionCompleteDelegateHandle = SessionInterface->AddOnStartSessionCompleteDelegate_Handle(OnStartSessionCompleteDelegate);

			/* Start the session. */
			SessionInterface->StartSession(GameSessionName);
		}
	}
}

void AValorGameSession::HandleMatchHasEnded()
{
	const IOnlineSubsystem* OnlineSubsystem = IOnlineSubsystem::Get();
	if (OnlineSubsystem)
	{
		IOnlineSessionPtr SessionInterface = OnlineSubsystem->GetSessionInterface();
		if (SessionInterface.IsValid())
		{
			// Inform all clients to end the match.
			for (FConstPlayerControllerIterator Iterator = GetWorld()->GetPlayerControllerIterator(); Iterator; ++Iterator)
			{
				AValorPlayerController* PlayerController = Cast<AValorPlayerController>(*Iterator);
				if (PlayerController && PlayerController->IsLocalPlayerController())
				{
					PlayerController->ClientEndOnlineMatch();
				}
			}

			/* End the session. */
			UE_LOG(LogValorServer, Log, TEXT("Ending session %s on server."), *GameSessionName.ToString());
			SessionInterface->EndSession(GameSessionName);
		}
	}
}

bool AValorGameSession::TravelToSession(int32 ControllerId, FName SessionName)
{
	const IOnlineSubsystem* OnlineSubystem = IOnlineSubsystem::Get();
	if (OnlineSubystem)
	{
		FString URL;
		IOnlineSessionPtr SessionInterface = OnlineSubystem->GetSessionInterface();
		if (SessionInterface.IsValid() && SessionInterface->GetResolvedConnectString(SessionName, URL))
		{
			APlayerController* PlayerController = UGameplayStatics::GetPlayerController(GetWorld(), ControllerId);
			if (PlayerController)
			{
				PlayerController->ClientTravel(URL, TRAVEL_Absolute);
				return true;
			}
		}
		else
		{
			UE_LOG(LogValorServer, Warning, TEXT("Failed to join session '%s'"), *SessionName.ToString());
		}
	}
#if !UE_BUILD_SHIPPING
	else
	{
		APlayerController* PlayerController = UGameplayStatics::GetPlayerController(GetWorld(), ControllerId);
		if (PlayerController)
		{
			FString LocalURL(TEXT("127.0.0.1"));
			PlayerController->ClientTravel(LocalURL, TRAVEL_Absolute);
			return true;
		}
	}
#endif //!UE_BUILD_SHIPPING

	return false;
}

bool AValorGameSession::IsBusy() const
{
	// HostSettings and SearchSettings are only valid if the session is busy.
	if (HostSettings.IsValid() || SearchSettings.IsValid())
	{
		return true;
	}

	const IOnlineSubsystem* OnlineSubsystem = IOnlineSubsystem::Get();
	if (OnlineSubsystem)
	{
		IOnlineSessionPtr SessionInterface = OnlineSubsystem->GetSessionInterface();
		if (SessionInterface.IsValid())
		{
			EOnlineSessionState::Type GameSessionState = SessionInterface->GetSessionState(GameSessionName);
			EOnlineSessionState::Type PartySessionState = SessionInterface->GetSessionState(PartySessionName);

			/* The game annd party sessions should both be NoSession if they are not busy. */
			if (GameSessionState != EOnlineSessionState::NoSession || PartySessionState != EOnlineSessionState::NoSession)
			{
				return true;
			}
		}
	}

	return false;
}

EOnlineAsyncTaskState::Type AValorGameSession::GetSearchResultStatus(int32& SearchResultIdx, int32& NumSearchResults)
{
	SearchResultIdx = 0;
	NumSearchResults = 0;

	if (SearchSettings.IsValid())
	{
		if (SearchSettings->SearchState == EOnlineAsyncTaskState::Done)
		{
			SearchResultIdx = CurrentSessionParams.BestSessionIdx;
			NumSearchResults = SearchSettings->SearchResults.Num();
		}
		return SearchSettings->SearchState;
	}

	return EOnlineAsyncTaskState::NotStarted;
}

const TArray<FOnlineSessionSearchResult>& AValorGameSession::GetSearchResults() const
{
	return SearchSettings->SearchResults;
}

void AValorGameSession::SetHostSettingsValues(TSharedPtr<class FValorOnlineSessionSettings> Settings, const FString& GameType, const FString& MapName)
{
	Settings->Set(SETTING_GAMEMODE, GameType, EOnlineDataAdvertisementType::ViaOnlineService);
	Settings->Set(SETTING_MAPNAME, MapName, EOnlineDataAdvertisementType::ViaOnlineService);
	Settings->Set(SETTING_MATCHING_HOPPER, FString("UnknownGameMode"), EOnlineDataAdvertisementType::DontAdvertise);
	Settings->Set(SETTING_MATCHING_TIMEOUT, 120.f, EOnlineDataAdvertisementType::ViaOnlineService);
	Settings->Set(SETTING_SESSION_TEMPLATE_NAME, FString("ValorGameSession"), EOnlineDataAdvertisementType::DontAdvertise);
	Settings->Set(SEARCH_KEYWORDS, ValorKeywords::CustomMatchKeyword, EOnlineDataAdvertisementType::ViaOnlineService);
}

bool AValorGameSession::HostSession(TSharedPtr<const FUniqueNetId> UserId, FName SessionName, const FString& GameType, const FString& MapName, bool bIsLan, bool bIsPresence, int32 MaxNumPlayers)
{
	const IOnlineSubsystem* OnlineSubsystem = IOnlineSubsystem::Get();
	if (OnlineSubsystem)
	{
		CurrentSessionParams.SessionName = SessionName;
		CurrentSessionParams.bIsLan = bIsLan;
		CurrentSessionParams.bIsPresence = bIsPresence;
		CurrentSessionParams.UserId = UserId;
		MaxPlayers = MaxNumPlayers;

		IOnlineSessionPtr SessionInterface = OnlineSubsystem->GetSessionInterface();
		if (SessionInterface.IsValid() && CurrentSessionParams.UserId.IsValid())
		{
			HostSettings = MakeShareable(new FValorOnlineSessionSettings(bIsLan, bIsPresence, MaxPlayers));
			SetHostSettingsValues(HostSettings, GameType, MapName);

			/* Bind the OnCreateSessionCompleteDelegate. */
			OnCreateSessionCompleteDelegateHandle = SessionInterface->AddOnCreateSessionCompleteDelegate_Handle(OnCreateSessionCompleteDelegate);

			/* Create the session. */
			return SessionInterface->CreateSession(*CurrentSessionParams.UserId, CurrentSessionParams.SessionName, *HostSettings);
		}
	}
#if !UE_BUILD_SHIPPING
	else
	{
		/* We are offline, but we want to hack workflow in development. */
		OnCreatePresenceSessionComplete().Broadcast(GameSessionName, true);
		return true;
	}
#endif

	return false;
}