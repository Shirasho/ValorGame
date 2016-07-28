// Copyright Shirasho Media 2016. All rights reserved.

#include "ValorGame.h"
#include "ValorCharacterMovementComponent.h"


UValorCharacterMovementComponent::UValorCharacterMovementComponent(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer)
{
	bUseAccelerationForPaths = true;
}

float UValorCharacterMovementComponent::GetMaxSpeed() const
{
	float MaxSpeed = Super::GetMaxSpeed();

	return MaxSpeed;
}
