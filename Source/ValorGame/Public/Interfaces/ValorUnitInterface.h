// Copyright Shirasho Media 2016. All rights reserved.

#pragma once

#include "ValorTypes.h"
#include "ValorUnitInterface.generated.h"

UINTERFACE(MinimalAPI)
class UValorUnitInterface : public UInterface
{
	GENERATED_UINTERFACE_BODY()
};

class IValorUnitInterface
{
	GENERATED_IINTERFACE_BODY()

	virtual EValorTeam GetTeam() const;
	virtual bool IsStealthed() const;
};