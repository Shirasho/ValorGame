// Copyright Shirasho Media 2016. All rights reserved.

#include "ValorGame.h"
#include "ValorMinionController.h"

#include "ValorMinion.h"

#include "BehaviorTree/BehaviorTree.h"
#include "BehaviorTree/BlackboardData.h"
#include "BehaviorTree/BehaviorTreeComponent.h"
#include "BehaviorTree/BlackboardComponent.h"

AValorMinionController::AValorMinionController(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer)
{
	//BlackboardComponent = ObjectInitializer.CreateDefaultSubobject<UBlackboardComponent>(this, TEXT("BlackBoardComponent"));
	BrainComponent = BehaviorComponent = ObjectInitializer.CreateDefaultSubobject<UBehaviorTreeComponent>(this, TEXT("BehaviorComponent"));
}

bool AValorMinionController::RunBehaviorTree(UBehaviorTree* BTAsset)
{
	if (ensureMsgf(BTAsset, TEXT("Null behavior tree provided to '%s'. Assign one in the editor."), *GetNameSafe(GetPawn())) &&
		ensureMsgf(BTAsset->BlackboardAsset, TEXT("Null blackboard asset for unit '%s'. Assign one in the editor."), *GetNameSafe(GetPawn())))
	{ 
		return Super::RunBehaviorTree(BTAsset);
	}

	return false;
}

AValorMinion* AValorMinionController::GetValorMinion() const
{
	return Cast<AValorMinion>(GetPawn());
}