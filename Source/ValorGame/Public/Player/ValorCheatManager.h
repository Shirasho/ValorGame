// Copyright Shirasho Media 2016. All rights reserved.

#pragma once

#include "ValorCheatManager.generated.h"

UCLASS(Within=ValorPlayerController)
class UValorCheatManager : public UCheatManager
{
	GENERATED_BODY()

public:

	UFUNCTION(Exec)
		void ForceMatchStart();

	UFUNCTION(Exec)
		void Cheat(const FString& Message);

	UFUNCTION(Exec)
		void SpawnBot(uint8 Team);
};
