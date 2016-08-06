// Copyright Shirasho Media 2016. All rights reserved.

#pragma once

#include "ValorAxisInputBinding.generated.h"

USTRUCT(BlueprintType)
struct FValorAxisInputBinding
{
	GENERATED_USTRUCT_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Input Song")
		FString AxisName;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Input Song")
		FString KeyAsString;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Input Song")
		FKey Key;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Input Song")
		float Scale = 1;

	FValorAxisInputBinding() {}
	FValorAxisInputBinding(const FString InAxisName, FKey InKey, float InScale)
		: Key(InKey)
		, KeyAsString(InKey.GetDisplayName().ToString())
		, AxisName(InAxisName)
		, Scale(InScale)
	{
	}

	FValorAxisInputBinding(const FInputAxisKeyMapping& Axis)
		: Key(Axis.Key)
		, KeyAsString(Axis.Key.GetDisplayName().ToString())
		, Scale(Axis.Scale)
	{
		AxisName = Axis.AxisName.ToString();
	}
};