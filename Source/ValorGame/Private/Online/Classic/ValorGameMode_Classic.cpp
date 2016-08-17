// Copyright Shirasho Media 2016. All rights reserved.

#include "ValorGame.h"
#include "ValorGameMode_Classic.h"

#include "ValorPlayerState_Classic.h"
#include "ValorGameState_Classic.h"
#include "ValorGameSession_Classic.h"

AValorGameMode_Classic::AValorGameMode_Classic(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer)
{
	PlayerStateClass = AValorPlayerState_Classic::StaticClass();
	GameStateClass = AValorGameState_Classic::StaticClass();
}

TSubclassOf<AGameSession> AValorGameMode_Classic::GetGameSessionClass() const
{
	return AValorGameSession_Classic::StaticClass();
}