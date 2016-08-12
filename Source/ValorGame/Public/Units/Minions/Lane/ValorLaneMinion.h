// Copyright Shirasho Media 2016. All rights reserved.

#pragma once

#include "ValorMinion.h"
#include "ValorLaneMinion.generated.h"

UCLASS(Abstract, BlueprintType, NotPlaceable)
class AValorLaneMinion : public AValorMinion
{
	GENERATED_BODY()

public:

	/* Spawns a lane minion and initializes the character. */
	virtual void Spawn(APlayerState* UsePlayerState = nullptr, void* ExtraData = nullptr) override;
};