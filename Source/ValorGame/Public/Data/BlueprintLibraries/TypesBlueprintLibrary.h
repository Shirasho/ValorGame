// Copyright Shirasho Media 2016. All rights reserved.

#pragma once

#include "TypesBlueprintLibrary.generated.h"

UCLASS()
class UTypesBlueprintLibrary : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()

public:

	UFUNCTION(BlueprintPure, Category = "Types", DisplayName = "String to Float Array")
		static bool K2_StringToFloatArray(UPARAM(ref) const TArray<FString>& InData, TArray<float>& OutData, int32 StartIndex = 0);

	UFUNCTION(BlueprintPure, Category = "Types", DisplayName = "String to Uint8 Array")
		static bool K2_StringToUint8Array(UPARAM(ref) const TArray<FString>& InData, TArray<uint8>& OutData, int32 StartIndex = 0);

	UFUNCTION(BlueprintPure, Category = "Types", DisplayName = "String to Uint32 Array")
		static bool K2_StringToInt32Array(UPARAM(ref) const TArray<FString>& InData, TArray<int32>& OutData, int32 StartIndex = 0);
};