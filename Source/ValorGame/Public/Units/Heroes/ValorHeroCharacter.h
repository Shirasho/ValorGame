// Copyright Shirasho Media 2016. All rights reserved.

#pragma once

#include "ValorCharacter.h"
#include "ValorAbilityInterface.h"
#include "ValorHeroInitializationProperties.h"
#include "ValorHeroCharacter.generated.h"

UCLASS(Abstract)
class AValorHeroCharacter : public AValorCharacter
{
	GENERATED_UCLASS_BODY()

protected:

	/* Default properties that apply to Heroes. */
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Replicated, Category = Defaults)
	FValorHeroInitializationProperties CharacterDefaults;

protected:

	IValorAbilityInterface* UnitAbilityOne;
	IValorAbilityInterface* UnitAbilityTwo;
	IValorAbilityInterface* UnitAbilityThree;
	IValorAbilityInterface* UnitAbilityFour;

public:

	//virtual void PreInitializeComponents() override;

	//virtual void PostInitializeComponents() override;

	virtual void BeginPlay() override;

	//virtual void EndPlay(const EEndPlayReason::Type EndPlayReason) override;

	//virtual void Tick(float DeltaSeconds) override;

public:

	FORCEINLINE const FValorHeroInitializationProperties& GetValorHeroInitilizationProperties() const
	{
		return CharacterDefaults;
	}
};