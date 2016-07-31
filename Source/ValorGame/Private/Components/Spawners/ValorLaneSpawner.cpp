// Copyright Shirasho Media 2016. All rights reserved.

#include "ValorGame.h"
#include "ValorLaneSpawner.h"

#include "ValorLaneMinion.h"
#include "ValorMinionController.h"

AValorLaneSpawner::AValorLaneSpawner(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer)
{
	UnitSpawnListIndex = 0;
}

void AValorLaneSpawner::SpawnUnit()
{
	if (HasAuthority())
	{
		if (UnitSpawnListIndex < SpawnClassOrder.Num())
		{
			FVector Location = GetActorLocation();
			FRotator Rotation = GetActorRotation();

			FActorSpawnParameters SpawnParameters;
			SpawnParameters.Owner = this;
			SpawnParameters.Instigator = Instigator;
			SpawnParameters.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AlwaysSpawn;

			AValorLaneMinion* Minion = Cast<AValorLaneMinion>(GetWorld()->SpawnActor(SpawnClassOrder[UnitSpawnListIndex], &Location, &Rotation, SpawnParameters));
			check(Minion);
			Minion->SetTeam(SpawnTeam);
			Minion->InitStats();

			AValorMinionController* MinionController = GetWorld()->SpawnActor<AValorMinionController>(Location, Rotation);
			check(MinionController);
			MinionController->Possess(Minion);

			if (ensureMsgf(Minion->BotBehavior, TEXT("Minion '%s' does not have a BehaviorTree assigned to it. Assign one in the editor."), *GetNameSafe(Minion)) &&
				ensureMsgf(Minion->BotBehavior->BlackboardAsset, TEXT("The BehaviorTree '%s' attached to Minion '%s' does not have a blackboard. Assign one in the editor."), *GetNameSafe(Minion->BotBehavior), *GetNameSafe(Minion)))
			{
				UBlackboardComponent* MinionBlackboardComponent;
				MinionController->UseBlackboard(Minion->BotBehavior->BlackboardAsset, MinionBlackboardComponent);
				MinionBlackboardComponent->SetValueAsObject(TEXT("NextMovementPoint"), InitialPoint);
				MinionController->RunBehaviorTree(Minion->BotBehavior);
			}

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