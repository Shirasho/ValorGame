// Copyright Shirasho Media 2016. All rights reserved.

#pragma once

#include "ValorCharacterStatTableRow.generated.h"

/* Structure that contains information about a hero's base stats. */
USTRUCT(BlueprintType)
struct FValorCharacterStatTableRow : public FTableRowBase
{
	GENERATED_USTRUCT_BODY()

public:

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Stats)
		float L1;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Stats)
		float L2;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Stats)
		float L3;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Stats)
		float L4;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Stats)
		float L5;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Stats)
		float L6;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Stats)
		float L7;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Stats)
		float L8;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Stats)
		float L9;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Stats)
		float L10;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Stats)
		float L11;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Stats)
		float L12;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Stats)
		float L13;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Stats)
		float L14;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Stats)
		float L15;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Stats)
		float L16;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Stats)
		float L17;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Stats)
		float L18;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Stats)
		float L19;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Stats)
		float L20;
};