// Copyright Shirasho Media 2016. All rights reserved.

#include "ValorGame.h"
#include "ValorHeroStatComponent.h"

#include "ValorPlayerState.h"

UValorHeroStatComponent::UValorHeroStatComponent(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer)
{
	
}

void UValorHeroStatComponent::Initialize(const class AValorPlayerState* PlayerState)
{
	Super::Initialize();

	Experience = PlayerState->GetPlayerExperience();
	UnitLevel = PlayerState->GetPlayerLevel();
}

int32 UValorHeroStatComponent::GetExperience() const
{
	const APawn* Owner = Cast<APawn>(GetOwner());
	check(Owner);

	const AValorPlayerState* ValorPlayerState = Cast<AValorPlayerState>(Owner->PlayerState);

	// For now all AI Hero units will have/require a PlayerState.
	check(ValorPlayerState);

	return ValorPlayerState->GetPlayerExperience();
}
void UValorHeroStatComponent::AdjustExperience(int32 Value)
{
	const APawn* Owner = Cast<APawn>(GetOwner());
	check(Owner);

	AValorPlayerState* ValorPlayerState = Cast<AValorPlayerState>(Owner->PlayerState);
	if (ensure(ValorPlayerState))
	{
		ValorPlayerState->AdjustExperience(Value);
		ValorPlayerState->IncrementPlayerLevel(RequiredExperiencePerLevel);
	}
	Super::AdjustExperience(Value);
}

uint8 UValorHeroStatComponent::GetUnitLevel() const
{
	const APawn* Owner = Cast<APawn>(GetOwner());
	check(Owner);

	const AValorPlayerState* ValorPlayerState = Cast<AValorPlayerState>(Owner->PlayerState);
	if (ensure(ValorPlayerState))
	{
		return ValorPlayerState->GetPlayerLevel();
	}

	return Experience;
}