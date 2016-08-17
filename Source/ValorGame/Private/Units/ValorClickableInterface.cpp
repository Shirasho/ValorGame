// Copyright Shirasho Media 2016. All rights reserved.

#include "ValorGame.h"
#include "ValorClickableInterface.h"

UValorClickableInterface::UValorClickableInterface(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer)
{

}

void IValorClickableInterface::OnMouseDown(UPrimitiveComponent* TouchedComponent, FKey ButtonPressed)
{

}

void IValorClickableInterface::OnMouseUp(UPrimitiveComponent* TouchedComponent, FKey ButtonPressed)
{

}