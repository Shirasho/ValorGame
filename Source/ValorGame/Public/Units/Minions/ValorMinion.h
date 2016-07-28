// Copyright Shirasho Media 2016. All rights reserved.

#pragma once

#include "ValorCharacter.h"
#include "ValorMinion.generated.h"

UCLASS(Abstract, NotBlueprintable, BlueprintType, NotPlaceable)
class AValorMinion : public AValorCharacter
{
	GENERATED_UCLASS_BODY()

public:

	UPROPERTY(EditAnywhere, Category = Behavior)
	class UBehaviorTree* BotBehavior;

public:

	//virtual void PreInitializeComponents() override;

	//virtual void PostInitializeComponents() override;

	//virtual void BeginPlay() override;

	//virtual void EndPlay(const EEndPlayReason::Type EndPlayReason) override;

	//virtual void Tick(float DeltaSeconds) override;
};