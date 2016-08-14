// Copyright Shirasho Media 2016. All rights reserved.

#include "ValorGame.h"
#include "ValorHeroStatComponent.h"

#include "ValorCharacter.h"
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

	if (ensure(ValorPlayerState))
	{
		UValorHeroStatComponent* MutableThis = const_cast<UValorHeroStatComponent*>(this);
		MutableThis->Experience = ValorPlayerState->GetPlayerExperience();
	}
	return Experience;
}
void UValorHeroStatComponent::AdjustExperience(int32 Value)
{
	APawn* Owner = Cast<APawn>(GetOwner());
	check(Owner);

	AValorPlayerState* ValorPlayerState = Cast<AValorPlayerState>(Owner->PlayerState);
	if (ensure(ValorPlayerState))
	{
		ValorPlayerState->AdjustExperience(Value);
		uint8 TimesLeveledUp = ValorPlayerState->IncrementPlayerLevel(RequiredExperiencePerLevel);

		UnitLevel += TimesLeveledUp;

		AValorCharacter* VOwner = Cast<AValorCharacter>(Owner);
		check(VOwner);

		for (TimesLeveledUp; TimesLeveledUp > 0; --TimesLeveledUp)
		{
			VOwner->OnLevelUp();
		}
	}
}

uint8 UValorHeroStatComponent::GetUnitLevel() const
{
	const APawn* Owner = Cast<APawn>(GetOwner());
	check(Owner);

	const AValorPlayerState* ValorPlayerState = Cast<AValorPlayerState>(Owner->PlayerState);
	if (ensure(ValorPlayerState))
	{
		UValorHeroStatComponent* MutableThis = const_cast<UValorHeroStatComponent*>(this);
		MutableThis->UnitLevel = ValorPlayerState->GetPlayerLevel();
	}

	return UnitLevel;
}