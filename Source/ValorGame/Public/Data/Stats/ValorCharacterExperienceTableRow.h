// Copyright Shirasho Media 2016. All rights reserved.

#pragma once

#include "ValorCharacterExperienceTableRow.generated.h"

/* Structure that contains information about a hero's base stats. */
USTRUCT(BlueprintType)
struct FValorCharacterExperienceTableRow : public FTableRowBase
{
	GENERATED_USTRUCT_BODY()

public:

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Stats)
		int32 L2;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Stats)
		int32 L3;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Stats)
		int32 L4;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Stats)
		int32 L5;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Stats)
		int32 L6;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Stats)
		int32 L7;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Stats)
		int32 L8;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Stats)
		int32 L9;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Stats)
		int32 L10;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Stats)
		int32 L11;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Stats)
		int32 L12;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Stats)
		int32 L13;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Stats)
		int32 L14;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Stats)
		int32 L15;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Stats)
		int32 L16;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Stats)
		int32 L17;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Stats)
		int32 L18;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Stats)
		int32 L19;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Stats)
		int32 L20;
};