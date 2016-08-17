// Copyright Shirasho Media 2016. All rights reserved.

#include "ValorGame.h"
#include "ValorLaneMinion.h"

#include "ValorMinionTargetPoint.h"

void AValorLaneMinion::Spawn(APlayerState* UsePlayerState, void* ExtraData)
{
	if (HasAuthority())
	{
		DECLARE_SCOPE_CYCLE_COUNTER(TEXT("AValorCharacter::TakeDamage"), STAT_ValorCharacter_TakeDamage, STATGROUP_ValorCharacter);

		Super::Spawn(UsePlayerState, ExtraData);

		if (ensureMsgf(BotBehavior, TEXT("Minion '%s' does not have a BehaviorTree assigned to it. Assign one in the editor."), *GetNameSafe(this)) &&
			ensureMsgf(BotBehavior->BlackboardAsset, TEXT("The BehaviorTree '%s' attached to Minion '%s' does not have a blackboard. Assign one in the editor."), *GetNameSafe(BotBehavior), *GetNameSafe(this)))
		{
			UBlackboardComponent* MinionBlackboardComponent;
			MinionController->UseBlackboard(BotBehavior->BlackboardAsset, MinionBlackboardComponent);

			AValorMinionTargetPoint* InitialPoint = static_cast<AValorMinionTargetPoint*>(ExtraData);
			check(InitialPoint);

			MinionBlackboardComponent->SetValueAsObject(TEXT("NextMovementPoint"), InitialPoint);
			MinionController->RunBehaviorTree(BotBehavior);
		}
	}
}