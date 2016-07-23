// Copyright Shirasho Media 2016. All rights reserved.

#pragma once

#include "ValorCharacter.h"
#include "ValorAICharacter.generated.h"

UCLASS()
class AValorAICharacter : public AValorCharacter
{
	GENERATED_UCLASS_BODY()

public:

	UPROPERTY(EditAnywhere, Category = Behavior)
	class UBehaviorTree* BotBehavior;
};