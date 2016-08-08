// Copyright Shirasho Media 2016. All rights reserved.

#pragma once

#include "ValorAbilityInterface.generated.h"

UINTERFACE(MinimalAPI)
class UValorAbilityInterface : public UInterface
{
	GENERATED_UINTERFACE_BODY()
};

class IValorAbilityInterface
{
	GENERATED_IINTERFACE_BODY()

	virtual FText GetAbilityDescription();
};