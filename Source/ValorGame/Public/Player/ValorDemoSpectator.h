// Copyright Shirasho Media 2016. All rights reserved.

#pragma once

#include "ValorDemoSpectator.generated.h"

UCLASS(Config=Game)
class AValorDemoSpectator : public APlayerController
{
	GENERATED_UCLASS_BODY()

public:

	virtual void SetupInputComponent() override;
	virtual void SetPlayer(UPlayer* Player) override;
	virtual void Destroyed() override;

	void OnToggleMenuPressed();
	void OnIncreasePlaybackSpeedPressed();
	void OnDecreasePlaybackSpeedPressed();

	int32 PlaybackSpeed;
};