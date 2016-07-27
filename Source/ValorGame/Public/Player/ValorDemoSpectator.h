// Copyright Shirasho Media 2016. All rights reserved.

#pragma once

#include "ValorDemoSpectator.generated.h"

UCLASS(Config=Game)
class AValorDemoSpectator : public APlayerController
{
	GENERATED_UCLASS_BODY()

public:

	//virtual void PreInitializeComponents() override;

	//virtual void PostInitializeComponents() override;

	//virtual void BeginPlay() override;

	//virtual void EndPlay(const EEndPlayReason::Type EndPlayReason) override;

	//virtual void Tick(float DeltaSeconds) override;

	virtual void SetupInputComponent() override;

	virtual void SetPlayer(UPlayer* Player) override;

	virtual void Destroyed() override;

public:

	void OnToggleMenuPressed();
	void OnIncreasePlaybackSpeedPressed();
	void OnDecreasePlaybackSpeedPressed();

	int32 PlaybackSpeed;
};