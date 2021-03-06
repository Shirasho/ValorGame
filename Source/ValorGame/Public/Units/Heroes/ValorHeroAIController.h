// Copyright Shirasho Media 2016. All rights reserved.

#pragma once

#include "AIController.h"
#include "ValorHeroAIController.generated.h"

UCLASS(Config = Game)
class AValorHeroAIController : public AAIController
{
	GENERATED_UCLASS_BODY()

protected:

	UBlackboardComponent* HeroBlackboardComponent;

public:

	//virtual void PreInitializeComponents() override;

	//virtual void PostInitializeComponents() override;

	//virtual void BeginPlay() override;

	//virtual void EndPlay(const EEndPlayReason::Type EndPlayReason) override;

	//virtual void Tick(float DeltaSeconds) override;

public:

	FORCEINLINE UBlackboardComponent* GetBlackboardComponent() const
	{
		return HeroBlackboardComponent;
	}

	void SetBlackboardComponent(UBlackboardComponent* InBlackboardComponent);
};