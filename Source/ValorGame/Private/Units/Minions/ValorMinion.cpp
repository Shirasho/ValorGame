// Copyright Shirasho Media 2016. All rights reserved.

#include "ValorGame.h"
#include "ValorMinion.h"

#include "ValorMinionController.h"

AValorMinion::AValorMinion(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer)
{
	AIControllerClass = AValorMinionController::StaticClass();
}

void AValorMinion::Spawn(APlayerState* UsePlayerState, const FValorVariantData& ExtraData)
{
	Spawn(UsePlayerState, nullptr);
}

void AValorMinion::Spawn(APlayerState* UsePlayerState, void* ExtraData)
{
	if (HasAuthority())
	{
		DECLARE_SCOPE_CYCLE_COUNTER(TEXT("AValorMinion::Spawn"), STAT_ValorMinion_Spawn, STATGROUP_ValorCharacter);

		// Minions can't have PlayerStates at this point in time.
		check(UsePlayerState == nullptr);

		Initialize();

		MinionController = GetWorld()->SpawnActor<AValorMinionController>(GetActorLocation(), GetActorRotation());
		check(MinionController);
		MinionController->Possess(this);
	}
}