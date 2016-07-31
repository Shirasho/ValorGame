// Copyright Shirasho Media 2016. All rights reserved.

#pragma once

#include "ValorMinionSpawner.h"
#include "ValorLaneSpawner.generated.h"

class AValorMinionTargetPoint;

UCLASS(Blueprintable, ClassGroup = Valor)
class AValorLaneSpawner : public AValorMinionSpawner
{
	GENERATED_UCLASS_BODY()

public:

	UPROPERTY(EditInstanceOnly, BlueprintReadOnly, Category = Spawner)
	AValorMinionTargetPoint* InitialPoint;

	/* The order of minions that spawn from this spawner. */
	UPROPERTY(EditInstanceOnly, BlueprintReadOnly, Category = Spawner)
	TArray<TSubclassOf<class AValorLaneMinion>> SpawnClassOrder;

	/* The time, in seconds, between minion spawns. Note that this value
	 * does not correspond to the time between waves - it corresponds to
	 * the time between minion spawns in the same wave. */
	UPROPERTY(EditInstanceOnly, BlueprintReadOnly, Category = Spawner)
	float TimeBetweenMinions;

private:

	FTimerHandle TimerHandle_SpawnUnit;
	uint8 UnitSpawnListIndex;

public:

	virtual void SpawnUnit() override;
};