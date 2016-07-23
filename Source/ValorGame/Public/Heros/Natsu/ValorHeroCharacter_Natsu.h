// Copyright Shirasho Media 2016. All rights reserved.

#pragma once

#include "ValorHeroCharacter.h"
#include "ValorHeroCharacter_Natsu.generated.h"

UCLASS(Abstract, BlueprintType, Blueprintable)
class AValorHeroCharacter_Natsu : public AValorHeroCharacter
{
	GENERATED_UCLASS_BODY()

public:

	virtual void PostInitializeComponents() override;

	virtual void Tick(float DeltaSeconds) override;
};