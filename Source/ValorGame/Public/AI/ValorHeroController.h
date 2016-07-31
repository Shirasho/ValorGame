// Copyright Shirasho Media 2016. All rights reserved.

#pragma once

#include "ValorAIController.h"
#include "ValorHeroController.generated.h"

class AValorHeroCharacter;

UCLASS(Config=Game)
class AValorHeroController : public AValorAIController
{
	GENERATED_UCLASS_BODY()

private:

	UPROPERTY(Transient)
		UBlackboardComponent* BlackboardComponent;

	UPROPERTY(Transient)
		UBehaviorTreeComponent* BehaviorComponent;

public:

	AValorHeroCharacter* GetValorHeroCharacter() const;

	FORCEINLINE UBlackboardComponent* GetBlackboardComponent() const
	{
		return BlackboardComponent;
	}
	FORCEINLINE UBehaviorTreeComponent* GetBehaviorComponent() const
	{
		return BehaviorComponent;
	}
};