// Copyright Shirasho Media 2016. All rights reserved.

#include "ValorGame.h"
#include "ValorAIController.h"

#include "ValorAICharacter.h"

#include "BehaviorTree/BehaviorTreeComponent.h"
#include "BehaviorTree/BlackboardComponent.h"

AValorAIController::AValorAIController(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer)
{
	BlackboardComponent = ObjectInitializer.CreateDefaultSubobject<UBlackboardComponent>(this, TEXT("BlackBoardComponent"));

	BrainComponent = BehaviorComponent = ObjectInitializer.CreateDefaultSubobject<UBehaviorTreeComponent>(this, TEXT("BehaviorComponent"));

	//bWantsPlayerState = true;
}

AValorAICharacter* AValorAIController::GetValorAICharacter() const
{
	return Cast<AValorAICharacter>(GetPawn());
}