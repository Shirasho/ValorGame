// Copyright Shirasho Media 2016. All rights reserved.

#pragma once

#include "AIController.h"
#include "ValorMinionController.generated.h"

class AValorMinion;

UCLASS(Config=Game)
class AValorMinionController : public AAIController
{
	GENERATED_UCLASS_BODY()

private:

	UPROPERTY(Transient)
	UBlackboardComponent* BlackboardComponent;

	UPROPERTY(Transient)
	UBehaviorTreeComponent* BehaviorComponent;

public:

	//virtual void PreInitializeComponents() override;

	//virtual void PostInitializeComponents() override;

	//virtual void BeginPlay() override;

	//virtual void EndPlay(const EEndPlayReason::Type EndPlayReason) override;

	//virtual void Tick(float DeltaSeconds) override;

public:

	AValorMinion* GetValorMinion() const;

	FORCEINLINE UBlackboardComponent* GetBlackboardComponent() const 
	{ 
		return BlackboardComponent;
	}
	FORCEINLINE UBehaviorTreeComponent* GetBehaviorComponent() const
	{ 
		return BehaviorComponent;
	}
};