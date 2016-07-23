// Copyright Shirasho Media 2016. All rights reserved.

#include "ValorGame.h"
#include "ValorAICharacter.h"
#include "ValorAIController.h"

AValorAICharacter::AValorAICharacter(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer)
{
	AIControllerClass = AValorAIController::StaticClass();

	bUseControllerRotationYaw = true;
}