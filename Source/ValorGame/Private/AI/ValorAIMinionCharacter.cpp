// Copyright Shirasho Media 2016. All rights reserved.

#include "ValorGame.h"
#include "ValorAIMinionCharacter.h"
#include "ValorAIMinionController.h"

AValorAIMinionCharacter::AValorAIMinionCharacter(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer)
{
	AIControllerClass = AValorAIMinionController::StaticClass();
}