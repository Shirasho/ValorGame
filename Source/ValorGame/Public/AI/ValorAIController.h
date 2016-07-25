// Copyright Shirasho Media 2016. All rights reserved.

#pragma once

#include "AIController.h"
#include "ValorAIController.generated.h"

class AValorAICharacter;

UCLASS(Abstract, Config=Game)
class AValorAIController : public AAIController
{
	GENERATED_UCLASS_BODY()

private:

	UPROPERTY(Transient)
	UBlackboardComponent* BlackboardComponent;

	UPROPERTY(Transient)
	UBehaviorTreeComponent* BehaviorComponent;

public:

	void PostInitializeComponents() override;

public:

	AValorAICharacter* GetValorAICharacter() const;

	FORCEINLINE UBlackboardComponent* GetBlackboardComponent() const 
	{ 
		return BlackboardComponent;
	}
	FORCEINLINE UBehaviorTreeComponent* GetBehaviorComponent() const
	{ 
		return BehaviorComponent;
	}
};