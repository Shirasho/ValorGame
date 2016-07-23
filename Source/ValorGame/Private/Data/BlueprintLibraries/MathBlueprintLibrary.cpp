// Copyright Shirasho Media 2016. All rights reserved.

#include "ValorGame.h"
#include "MathBlueprintLibrary.h"


float UMathBlueprintLibrary::SetPrecision_Float(float Value, uint8 DecimalPlaces)
{
    float PowerValue = FMath::Pow(10, DecimalPlaces);
    return (float)(FMath::FloorToInt(Value * PowerValue)) / PowerValue;
}

double UMathBlueprintLibrary::SetPrecision_Double(double Value, uint8 DecimalPlaces)
{
    double PowerValue = FMath::Pow(10, DecimalPlaces);
    return (double)(FMath::FloorToInt(Value * PowerValue)) / PowerValue;
}