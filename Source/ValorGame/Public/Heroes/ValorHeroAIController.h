// Copyright Shirasho Media 2016. All rights reserved.

#pragma once

#include "AIController.h"
#include "ValorHeroAIController.generated.h"

UCLASS(Config = Game)
class AValorHeroAIController : public AAIController
{
	GENERATED_UCLASS_BODY()

public:

	void PostInitializeComponents() override;
};