// Copyright Shirasho Media 2016. All rights reserved.

#include "ValorGame.h"
#include "ValorSpectatorPawn.h"


void AValorSpectatorPawn::SetupPlayerInputComponent(UInputComponent* InputComponent)
{

    Super::SetupPlayerInputComponent(InputComponent);

    check(InputComponent);

    /* OnLeftMouse */
    InputComponent->BindAction("PrimaryAction1", IE_Pressed, this, &AValorSpectatorPawn::OnPrimaryAction1Pressed);

    /* OnMouseWheel */
    InputComponent->BindAction("CameraZoomIn", IE_Pressed, this, &AValorSpectatorPawn::OnCameraZoomInPressed);
    InputComponent->BindAction("CameraZoomOut", IE_Pressed, this, &AValorSpectatorPawn::OnCameraZoomOutPressed);

    /* OnCameraPan */
    InputComponent->BindAction("PanCameraLeft", IE_Pressed, this, &AValorSpectatorPawn::OnCameraPanLeftPressed);
    InputComponent->BindAction("PanCameraLeft", IE_Released, this, &AValorSpectatorPawn::OnCameraPanLeftReleased);

    InputComponent->BindAction("PanCameraRight", IE_Pressed, this, &AValorSpectatorPawn::OnCameraPanRightPressed);
    InputComponent->BindAction("PanCameraRight", IE_Released, this, &AValorSpectatorPawn::OnCameraPanRightReleased);

    InputComponent->BindAction("PanCameraUp", IE_Pressed, this, &AValorSpectatorPawn::OnCameraPanUpPressed);
    InputComponent->BindAction("PanCameraUp", IE_Released, this, &AValorSpectatorPawn::OnCameraPanUpReleased);

    InputComponent->BindAction("PanCameraDown", IE_Pressed, this, &AValorSpectatorPawn::OnCameraPanDownPressed);
    InputComponent->BindAction("PanCameraDown", IE_Released, this, &AValorSpectatorPawn::OnCameraPanDownReleased);

    /* OnMenu */
    InputComponent->BindAction("ToggleMenu", IE_Pressed, this, &AValorSpectatorPawn::OnToggleMenuPressed);
}

void AValorSpectatorPawn::OnPrimaryAction1Pressed()
{

}

void AValorSpectatorPawn::OnCameraZoomInPressed()
{

}

void AValorSpectatorPawn::OnCameraZoomOutPressed()
{

}

void AValorSpectatorPawn::OnCameraPanLeftPressed()
{

}

void AValorSpectatorPawn::OnCameraPanLeftReleased()
{

}

void AValorSpectatorPawn::OnCameraPanRightPressed()
{

}

void AValorSpectatorPawn::OnCameraPanRightReleased()
{

}

void AValorSpectatorPawn::OnCameraPanUpPressed()
{

}

void AValorSpectatorPawn::OnCameraPanUpReleased()
{

}

void AValorSpectatorPawn::OnCameraPanDownPressed()
{

}

void AValorSpectatorPawn::OnCameraPanDownReleased()
{

}

void AValorSpectatorPawn::OnToggleMenuPressed()
{

}

void AValorSpectatorPawn::OnToggleScoreboardPressed()
{

}