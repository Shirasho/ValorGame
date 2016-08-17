// Copyright Shirasho Media 2016. All rights reserved.

#include "ValorGame.h"
#include "ValorLaneSpawner.h"

#include "ValorLaneMinion.h"

AValorLaneSpawner::AValorLaneSpawner(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer)
{
	UnitSpawnListIndex = 0;
}

void AValorLaneSpawner::SpawnUnit()
{
	DECLARE_SCOPE_CYCLE_COUNTER(TEXT("AValorLaneSpawner::SpawnUnit"), STAT_ValorLaneSpawner_SpawnUnit, STATGROUP_ValorSpawner);

	if (HasAuthority() && SpawnClassOrder.Num() > 0)
	{
		if (UnitSpawnListIndex < SpawnClassOrder.Num() && SpawnClassOrder[UnitSpawnListIndex])
		{
			FVector Location = GetActorLocation();
			FRotator Rotation = GetActorRotation();

			FActorSpawnParameters SpawnParameters;
			SpawnParameters.Owner = this;
			SpawnParameters.Instigator = Instigator;
			SpawnParameters.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AdjustIfPossibleButAlwaysSpawn;

			AValorLaneMinion* Minion = Cast<AValorLaneMinion>(GetWorld()->SpawnActor(SpawnClassOrder[UnitSpawnListIndex], &Location, &Rotation, SpawnParameters));
			check(Minion);
			Minion->Spawn(nullptr, InitialPoint);
			Minion->SetTeam(SpawnTeam);

			++UnitSpawnListIndex;

			GetWorld()->GetTimerManager().SetTimer(TimerHandle_SpawnUnit, this, &AValorLaneSpawner::SpawnUnit, GetWorld()->GetWorldSettings()->GetEffectiveTimeDilation() * TimeBetweenMinions, false);
		}
		else
		{
			// Reset the list index and stop spawning.
			UnitSpawnListIndex = 0;
		}
	}
}