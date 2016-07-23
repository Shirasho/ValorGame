// Copyright Shirasho Media 2016. All rights reserved.

#include "ValorGame.h"
#include "ValorGameState.h"


AValorGameState::AValorGameState(const FObjectInitializer& ObjectInitializer) 
	: Super(ObjectInitializer)
{
	bTimerPaused = false;
}

void AValorGameState::GetLifetimeReplicatedProps(TArray< FLifetimeProperty > & OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);

	DOREPLIFETIME(AValorGameState, TeamKills);
	DOREPLIFETIME(AValorGameState, TeamDeaths);
	DOREPLIFETIME(AValorGameState, TeamAssists);
	DOREPLIFETIME(AValorGameState, bTimerPaused);
}