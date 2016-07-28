// Copyright Shirasho Media 2016. All rights reserved.

#include "ValorGame.h"
#include "ValorMinionController.h"

#include "ValorMinion.h"

#include "BehaviorTree/BehaviorTreeComponent.h"
#include "BehaviorTree/BlackboardComponent.h"

AValorMinionController::AValorMinionController(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer)
{
	BlackboardComponent = ObjectInitializer.CreateDefaultSubobject<UBlackboardComponent>(this, TEXT("BlackBoardComponent"));

	BrainComponent = BehaviorComponent = ObjectInitializer.CreateDefaultSubobject<UBehaviorTreeComponent>(this, TEXT("BehaviorComponent"));
}

AValorMinion* AValorMinionController::GetValorMinion() const
{
	return Cast<AValorMinion>(GetPawn());
}