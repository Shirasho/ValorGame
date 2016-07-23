// Copyright Shirasho Media 2016. All rights reserved.

#pragma once

#include "ValorGameMode_Menu.generated.h"

UCLASS()
class AValorGameMode_Menu : public AGameMode
{
	GENERATED_UCLASS_BODY()

public:

	/* Override with empty method. The menu does not require a player restart. */
	virtual void RestartPlayer(class AController* NewPlayer) override;

	/* Returns the game session class to use. */
	virtual TSubclassOf<AGameSession> GetGameSessionClass() const override;
};