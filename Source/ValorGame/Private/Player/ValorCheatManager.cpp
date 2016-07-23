// Copyright Shirasho Media 2016. All rights reserved.

#include "ValorGame.h"
#include "ValorCheatManager.h"

#include "ValorPlayerController.h"
#include "ValorGameMode.h"
#include "ValorAIController.h"

void UValorCheatManager::ForceMatchStart()
{
	const AValorPlayerController* PlayerController = GetOuterAValorPlayerController();

	if (PlayerController)
	{
		AValorGameMode* GameMode = PlayerController->GetWorld()->GetAuthGameMode<AValorGameMode>();
		if (GameMode && GameMode->GetMatchState() == MatchState::WaitingToStart)
		{
			GameMode->StartMatch();
		}
	}
}

void UValorCheatManager::Cheat(const FString& Message)
{
	AValorPlayerController* PlayerController = GetOuterAValorPlayerController();

	if (PlayerController)
	{
		PlayerController->ServerCheat(Message.Left(128));
	}
}

void UValorCheatManager::SpawnBot(uint8 Team)
{
	/*const AValorPlayerController* PlayerController = GetOuterAValorPlayerController();

	if (PlayerController)
	{
		APawn* Pawn = PlayerController->GetPawn();
		AValorGameMode* GameMode = PlayerController->GetWorld()->GetAuthGameMode<AValorGameMode>();
		UWorld* World = PlayerController->GetWorld();

		if (Pawn && GameMode && World)
		{
			static int32 CheatBotNum = 200;
			AValorAIController* AIController = GameMode->CreateBot(CheatBotNum++);
			GameMode->RestartPlayer(AIController);
		}
	}*/
}