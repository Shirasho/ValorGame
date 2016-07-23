// Copyright Shirasho Media 2016. All rights reserved.

#pragma once

#include "ValorCharacterMovementComponent.generated.h"

UCLASS()
class UValorCharacterMovementComponent : public UCharacterMovementComponent
{

	GENERATED_UCLASS_BODY()

public:

	virtual float GetMaxSpeed() const override;
};