// Copyright Shirasho Media 2016. All rights reserved.

#pragma once

#include "ValorSpawnableInterface.generated.h"

UINTERFACE(MinimalAPI)
class UValorSpawnableInterface : public UInterface
{
	GENERATED_UINTERFACE_BODY()
};

class IValorSpawnableInterface
{
	GENERATED_IINTERFACE_BODY()

	virtual void Spawn(APlayerState* UsePlayerState = nullptr, const FValorVariantData& ExtraData = FValorVariantData());

	virtual void Spawn(APlayerState* UsePlayerState = nullptr, void* ExtraData = nullptr);
};