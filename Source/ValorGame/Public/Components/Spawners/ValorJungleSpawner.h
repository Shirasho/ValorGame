// Copyright Shirasho Media 2016. All rights reserved.

#pragma once

#include "ValorMinionSpawner.h"
#include "ValorJungleSpawner.generated.h"

UCLASS(Blueprintable, ClassGroup=Valor)
class AValorJungleSpawner : public AValorMinionSpawner
{
	GENERATED_BODY()

public:

	/* The minion class to spawn from this spawner. */
	UPROPERTY(EditInstanceOnly, Category = Spawner)
	TSubclassOf<class AValorJungleMinion> SpawnClass;
};