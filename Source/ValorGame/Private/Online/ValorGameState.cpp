// Copyright Shirasho Media 2016. All rights reserved.

#include "ValorGame.h"
#include "ValorGameState.h"


AValorGameState::AValorGameState(const FObjectInitializer& ObjectInitializer) 
	: Super(ObjectInitializer)
{
	bTimerPaused = false;
}

void AValorGameState::MulticastPlaySoundAtLocation_Implementation(/*UObject* WorldContextObject, */class USoundBase* Sound, FVector Location, FRotator Rotation, float VolumeMultiplier = 1.f, float PitchMultiplier = 1.f, float StartTime = 0.f, class USoundAttenuation* AttenuationSettings = nullptr, class USoundConcurrency* ConcurrencySettings = nullptr)
{
	if (GetNetMode() != NM_DedicatedServer)
	{
		UGameplayStatics::PlaySoundAtLocation(/*WorldContextObject*/ GetWorld(), Sound, Location, Rotation, VolumeMultiplier, PitchMultiplier, StartTime, AttenuationSettings, ConcurrencySettings);
	}
}

void AValorGameState::GetLifetimeReplicatedProps(TArray< FLifetimeProperty > & OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);

	DOREPLIFETIME(AValorGameState, TeamKills);
	DOREPLIFETIME(AValorGameState, TeamDeaths);
	DOREPLIFETIME(AValorGameState, TeamAssists);
	DOREPLIFETIME(AValorGameState, bTimerPaused);
}