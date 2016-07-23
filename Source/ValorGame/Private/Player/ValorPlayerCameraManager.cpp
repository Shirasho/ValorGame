// Copyright Shirasho Media 2016. All rights reserved.

#include "ValorGame.h"
#include "ValorPlayerCameraManager.h"

AValorPlayerCameraManager::AValorPlayerCameraManager(const FObjectInitializer& ObjectInitializer)
    : Super(ObjectInitializer)
{
    DefaultFOV = 90.f;
    ViewPitchMin = -87.0f;
    ViewPitchMax = 87.0f;
    bAlwaysApplyModifiers = true;
}