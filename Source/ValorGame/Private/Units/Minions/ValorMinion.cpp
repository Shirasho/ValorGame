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
		// Minions can't have PlayerStates at this point in time.
		check(UsePlayerState == nullptr);

		Initialize();

		MinionController = GetWorld()->SpawnActor<AValorMinionController>(GetActorLocation(), GetActorRotation());
		check(MinionController);
		MinionController->Possess(this);
	}
}