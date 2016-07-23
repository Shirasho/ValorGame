// Copyright Shirasho Media 2016. All rights reserved.

#pragma once

#include "ValorCharacterStatContainer.generated.h"

USTRUCT()
struct FValorCharacterStatContainer
{
	GENERATED_USTRUCT_BODY()

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Stats)
		float Health;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Stats)
		float PrimaryResource;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Stats)
		float SecondaryResource;
};