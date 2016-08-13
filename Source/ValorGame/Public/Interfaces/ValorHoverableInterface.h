// Copyright Shirasho Media 2016. All rights reserved.

#pragma once

#include "ValorHoverableInterface.generated.h"

UINTERFACE(MinimalAPI)
class UValorHoverableInterface : public UInterface
{
	GENERATED_UINTERFACE_BODY()
};

class IValorHoverableInterface
{
	GENERATED_IINTERFACE_BODY()

	virtual void OnMouseEnter(UPrimitiveComponent* TouchedComponent);
	virtual void OnMouseLeave(UPrimitiveComponent* TouchedComponent);
};