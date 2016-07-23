// Copyright Shirasho Media 2016. All rights reserved.

#pragma once

#include "ValorCharacterStatTableRow.generated.h"

/* Structure that contains information about how a hero progresses as they level up. */
USTRUCT(BlueprintType)
struct FValorCharacterStatTableRow : public FTableRowBase
{
	GENERATED_USTRUCT_BODY()

public:

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Stats)
		float BaseHealth;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Stats)
		float BaseHealthRegen;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Stats)
		float BasePrimaryResource;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Stats)
		float BasePrimaryResourceRegen;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Stats)
		float BaseSecondaryResource;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Stats)
		float BaseSecondaryResourceRegen;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Stats)
		uint8 MaxSecondaryResource;
};