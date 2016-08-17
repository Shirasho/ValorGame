// Copyright Shirasho Media 2016. All rights reserved.

#pragma once

#include "ValorGameMode.h"
#include "ValorGameMode_Classic.generated.h"


UCLASS(Config = Game)
class AValorGameMode_Classic : public AValorGameMode
{
	GENERATED_UCLASS_BODY()

public:

	//virtual void PreInitializeComponents() override;

	//virtual void PostInitializeComponents() override;

	//virtual void BeginPlay() override;

	//virtual void EndPlay(const EEndPlayReason::Type EndPlayReason) override;

	//virtual void Tick(float DeltaSeconds) override;

	/* Returns the game session class to use. */
	virtual TSubclassOf<AGameSession> GetGameSessionClass() const override;
};
