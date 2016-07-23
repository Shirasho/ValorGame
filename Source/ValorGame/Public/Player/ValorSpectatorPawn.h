// Copyright Shirasho Media 2016. All rights reserved.

#pragma once
#include "ValorSpectatorPawn.generated.h"


UCLASS(Config=Game, Blueprintable, BlueprintType)
class AValorSpectatorPawn : public ASpectatorPawn
{
    GENERATED_BODY()

public:

    virtual void SetupPlayerInputComponent(class UInputComponent* InputComponent) override;

protected:

    void OnPrimaryAction1Pressed();

    void OnCameraZoomInPressed();

    void OnCameraZoomOutPressed();

    void OnCameraPanLeftPressed();

    void OnCameraPanLeftReleased();

    void OnCameraPanRightPressed();

    void OnCameraPanRightReleased();

    void OnCameraPanUpPressed();

    void OnCameraPanUpReleased();

    void OnCameraPanDownPressed();

    void OnCameraPanDownReleased();

    void OnToggleMenuPressed();

    void OnToggleScoreboardPressed();
};
