// Copyright Shirasho Media 2016. All rights reserved.

#include "ValorGame.h"
#include "ValorGameMode_Menu.h"

#include "ValorPlayerController_Menu.h"
#include "ValorGameSession.h"


AValorGameMode_Menu::AValorGameMode_Menu(const FObjectInitializer& ObjectInitializer) : Super(ObjectInitializer)
{
	PlayerControllerClass = AValorPlayerController_Menu::StaticClass();
}

void AValorGameMode_Menu::RestartPlayer(class AController* NewPlayer)
{
	// Don't restart.
}

TSubclassOf<AGameSession> AValorGameMode_Menu::GetGameSessionClass() const
{
	return AValorGameSession::StaticClass();
}
