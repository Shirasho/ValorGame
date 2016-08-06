// Copyright Shirasho Media 2016. All rights reserved.

#pragma once

#include "DataBlueprintLibrary.generated.h"

UCLASS()
class UDataBlueprintLibrary : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()

public:

	UFUNCTION(BlueprintPure, Category = "Data", DisplayName = "Parse String Array (float)")
		static bool ParseStringArray_float(UPARAM(ref) const TArray<FString>& InData, TArray<float>& OutData, int32 StartIndex = 0);

	UFUNCTION(BlueprintPure, Category = "Data", DisplayName = "Parse String Array (uint8)")
		static bool ParseStringArray_uint8(UPARAM(ref) const TArray<FString>& InData, TArray<uint8>& OutData, int32 StartIndex = 0);

	UFUNCTION(BlueprintPure, Category = "Data", DisplayName = "Parse String Array (int32)")
		static bool ParseStringArray_int32(UPARAM(ref) const TArray<FString>& InData, TArray<int32>& OutData, int32 StartIndex = 0);
};