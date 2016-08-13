// Copyright Shirasho Media 2016. All rights reserved.

#include "ValorGame.h"
#include "ValorUnitInterface.h"

UValorUnitInterface::UValorUnitInterface(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer)
{

}

EValorTeam IValorUnitInterface::GetTeam() const
{
	unimplemented();
	return EValorTeam::Invalid;
}

bool IValorUnitInterface::IsStealthed() const
{
	return false;
}