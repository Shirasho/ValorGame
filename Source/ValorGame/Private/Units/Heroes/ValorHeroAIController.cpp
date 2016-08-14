// Copyright Shirasho Media 2016. All rights reserved.

#include "ValorGame.h"
#include "ValorHeroAIController.h"

AValorHeroAIController::AValorHeroAIController(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer)
{
}

void AValorHeroAIController::SetBlackboardComponent(UBlackboardComponent* InBlackboardComponent)
{
	HeroBlackboardComponent = InBlackboardComponent;
}