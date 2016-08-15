// Copyright Shirasho Media 2016. All rights reserved.

#include "ValorGame.h"
#include "ValorUnitInterface.h"

#include "ValorStatComponent.h"

UValorUnitInterface::UValorUnitInterface(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer)
{

}

EValorTeam IValorUnitInterface::GetTeam() const
{
	unimplemented();
	return EValorTeam::Invalid;
}
UValorStatComponent* IValorUnitInterface::GetStatComponent() const
{
	return nullptr;
}

bool IValorUnitInterface::IsStealthed() const
{
	return false;
}

bool IValorUnitInterface::IsAlive() const
{
	return false;
}