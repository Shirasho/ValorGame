// Copyright Shirasho Media 2016. All rights reserved.

#include "ValorGame.h"
#include "ValorHeroController.h"

#include "ValorHeroCharacter.h"

#include "BehaviorTree/BehaviorTreeComponent.h"
#include "BehaviorTree/BlackboardComponent.h"

AValorHeroController::AValorHeroController(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer)
{
	BlackboardComponent = ObjectInitializer.CreateDefaultSubobject<UBlackboardComponent>(this, TEXT("BlackBoardComponent"));

	BrainComponent = BehaviorComponent = ObjectInitializer.CreateDefaultSubobject<UBehaviorTreeComponent>(this, TEXT("BehaviorComponent"));
}

AValorHeroCharacter* AValorHeroController::GetValorHeroCharacter() const
{
	return Cast<AValorHeroCharacter>(GetPawn());
}