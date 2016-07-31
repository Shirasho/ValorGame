// Copyright Shirasho Media 2016. All rights reserved.

#pragma once

#include "ValorAIController.h"
#include "ValorMinionController.generated.h"

class AValorMinion;

UCLASS(Config=Game)
class AValorMinionController : public AValorAIController
{
	GENERATED_UCLASS_BODY()

private:

	UPROPERTY(Transient)
	UBehaviorTreeComponent* BehaviorComponent;

public:

	//virtual void PreInitializeComponents() override;

	//virtual void PostInitializeComponents() override;

	//virtual void BeginPlay() override;

	//virtual void EndPlay(const EEndPlayReason::Type EndPlayReason) override;

	//virtual void Tick(float DeltaSeconds) override;

	//virtual void Possess(APawn* InPawn) override;

	virtual bool RunBehaviorTree(UBehaviorTree* BTAsset) override;

public:

	AValorMinion* GetValorMinion() const;

	FORCEINLINE UBehaviorTreeComponent* GetBehaviorComponent() const
	{ 
		return BehaviorComponent;
	}

	FORCEINLINE UBlackboardComponent* GetBlackboardComponent() const
	{
		return Blackboard;
	}
};