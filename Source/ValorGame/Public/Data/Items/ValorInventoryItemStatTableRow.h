// Copyright Shirasho Media 2016. All rights reserved.

#pragma once

#include "ValorInventoryItemStatTableRow.generated.h"

/* Structure that contains information about how a hero progresses as they level up. */
USTRUCT(BlueprintType)
struct FValorInventoryItemStatTableRow : public FTableRowBase
{
	GENERATED_USTRUCT_BODY()

public:

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Stats)
		FText DisplayName;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Stats)
		FString DisplayTexture;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Stats)
		float BonusHealthFlat;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Stats)
		float BonusHealthPercentBase;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Stats)
		float BonusHealthPercentMax;


	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Stats)
		float BonusPrimaryResourceFlat;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Stats)
		float BonusPrimaryResourcePercentBase;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Stats)
		float BonusPrimaryResourcePercentMax;


	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Stats)
		float BonusHealthRegenFlat;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Stats)
		float BonusHealthRegenPercentBase;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Stats)
		float BonusHealthRegenPercentMax;


	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Stats)
		float BonusPrimaryResourceRegenFlat;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Stats)
		float BonusPrimaryResourceRegenPercentBase;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Stats)
		float BonusPrimaryResourceRegenPercentMax;
};