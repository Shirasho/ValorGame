// Copyright Shirasho Media 2016. All rights reserved.

#include "ValorGame.h"
#include "ValorMinion.h"

#include "ValorMinionController.h"

AValorMinion::AValorMinion(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer)
{
	AIControllerClass = AValorMinionController::StaticClass();
}