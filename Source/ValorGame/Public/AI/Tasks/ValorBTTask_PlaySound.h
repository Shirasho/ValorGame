// Copyright Shirasho Media 2016. All rights reserved.

#pragma once

#include "BehaviorTree/BTTaskNode.h"
#include "ValorBTTask_PlaySound.generated.h"

UCLASS()
class UValorBTTask_PlaySoundMulticast : public UBTTaskNode
{
	GENERATED_UCLASS_BODY()

public:

	/* The sound cue to play. */
	UPROPERTY(Category = Node, EditAnywhere)
		USoundCue* SoundToPlay;

	virtual EBTNodeResult::Type ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) override;
	virtual FString GetStaticDescription() const override;

#if WITH_EDITOR
	virtual FName GetNodeIconName() const override;
#endif // WITH_EDITOR
};