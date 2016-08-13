// Copyright Shirasho Media 2016. All rights reserved.

#pragma once

#include "ValorClickableInterface.generated.h"

UINTERFACE(MinimalAPI)
class UValorClickableInterface : public UInterface
{
	GENERATED_UINTERFACE_BODY()
};

class IValorClickableInterface
{
	GENERATED_IINTERFACE_BODY()

	virtual void OnMouseDown(UPrimitiveComponent* TouchedComponent, FKey ButtonPressed);
	virtual void OnMouseUp(UPrimitiveComponent* TouchedComponent, FKey ButtonPressed);
};