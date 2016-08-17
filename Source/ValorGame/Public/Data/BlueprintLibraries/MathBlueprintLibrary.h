// Copyright Shirasho Media 2016. All rights reserved.

#pragma once

#include "MathBlueprintLibrary.generated.h"

UCLASS()
class UMathBlueprintLibrary : public UBlueprintFunctionLibrary
{
    GENERATED_BODY()

public:

    UFUNCTION(BlueprintPure, Category = "Math|Float", DisplayName = "Set Precision (float)")
    static float K2_SetFloatPrecision(float Value, uint8 DecimalPlaces);

    // Double is not supported in Blueprints. Leaving this here for code classes to utilize.
    static double K2_SetDoublePrecision(double Value, uint8 DecimalPlaces);
};