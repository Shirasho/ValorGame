// Copyright Shirasho Media 2016. All rights reserved.

#include "ValorGame.h"
#include "ValorDemoSpectator.h"


AValorDemoSpectator::AValorDemoSpectator(const FObjectInitializer& ObjectInitializer) : Super(ObjectInitializer)
{
	bShowMouseCursor = true;
	PrimaryActorTick.bTickEvenWhenPaused = true;
	bShouldPerformFullTickWhenPaused = true;
}

void AValorDemoSpectator::SetupInputComponent()
{
	Super::SetupInputComponent();

	/* OnMenu */
	InputComponent->BindAction("ToggleMenu", IE_Pressed, this, &AValorDemoSpectator::OnToggleMenuPressed);

	InputComponent->BindAction("CameraZoomIn", IE_Pressed, this, &AValorDemoSpectator::OnIncreasePlaybackSpeedPressed);
	InputComponent->BindAction("CameraZoomOut", IE_Pressed, this, &AValorDemoSpectator::OnDecreasePlaybackSpeedPressed);
}

void AValorDemoSpectator::SetPlayer(UPlayer* InPlayer)
{
	Super::SetPlayer(InPlayer);

	PlaybackSpeed = 2;

	FInputModeGameAndUI InputMode;
	//InputMode.SetWidgetToFocus(DemoHUD);

	SetInputMode(InputMode);
}

void AValorDemoSpectator::OnToggleMenuPressed()
{
	// if no one's paused, pause
	/*if (ValorDemoPlaybackMenu.IsValid())
	{
		ValorDemoPlaybackMenu->ToggleGameMenu();
	}*/
}

static float PlaybackSpeedLUT[5] = { 0.1f, 0.5f, 1.0f, 2.0f, 4.0f };

void AValorDemoSpectator::OnIncreasePlaybackSpeedPressed()
{
	PlaybackSpeed = FMath::Clamp(PlaybackSpeed + 1, 0, 4);

	GetWorldSettings()->DemoPlayTimeDilation = PlaybackSpeedLUT[PlaybackSpeed];
}

void AValorDemoSpectator::OnDecreasePlaybackSpeedPressed()
{
	PlaybackSpeed = FMath::Clamp(PlaybackSpeed - 1, 0, 4);

	GetWorldSettings()->DemoPlayTimeDilation = PlaybackSpeedLUT[PlaybackSpeed];
}

void AValorDemoSpectator::Destroyed()
{
	//if (GEngine != nullptr && GEngine->GameViewport != nullptr && DemoHUD.IsValid())
	//{
	//	// Remove HUD
	//	GEngine->GameViewport->RemoveViewportWidgetContent(DemoHUD.ToSharedRef());
	//}

	Super::Destroyed();
}
