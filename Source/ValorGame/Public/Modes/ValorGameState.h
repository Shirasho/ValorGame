// Copyright Shirasho Media 2016. All rights reserved.

#pragma once

#include "ValorTypes.h"
#include "ValorGameState.generated.h"


UCLASS()
class AValorGameState : public AGameState
{
	GENERATED_UCLASS_BODY()

public:

	UPROPERTY(Transient, Replicated)
	TMap<EValorTeam, uint32> TeamKills;

	UPROPERTY(Transient, Replicated)
	TMap<EValorTeam, uint32> TeamDeaths;

	UPROPERTY(Transient, Replicated)
	TMap<EValorTeam, uint32> TeamAssists;

	UPROPERTY(Transient, Replicated)
	bool bTimerPaused;

public:

	//virtual void PreInitializeComponents() override;

	//virtual void PostInitializeComponents() override;

	//virtual void BeginPlay() override;

	//virtual void EndPlay(const EEndPlayReason::Type EndPlayReason) override;

	//virtual void Tick(float DeltaSeconds) override;
};