// Copyright Shirasho Media 2016. All rights reserved.

#pragma once

#include "ValorInventoryItemEffectInterface.generated.h"

UINTERFACE(MinimalAPI)
class UValorInventoryItemEffectInterface : public UInterface
{
	GENERATED_UINTERFACE_BODY()
};

class IValorInventoryItemEffectInterface
{
	GENERATED_IINTERFACE_BODY()

	virtual void ExecuteItemActive();
};