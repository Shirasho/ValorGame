// Copyright Shirasho Media 2016. All rights reserved.

#include "ValorGame.h"
#include "ValorAbilityInterface.h"

UValorAbilityInterface::UValorAbilityInterface(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer)
{

}

FText IValorAbilityInterface::GetAbilityDescription()
{
	// If you hit this it means this method was not overridden.
	// This method must be overridden and implemented in the owning class.
	unimplemented();

	return FText();
}