// Copyright Shirasho Media 2016. All rights reserved.

#include "ValorGame.h"
#include "ValorSpawnableInterface.h"

UValorSpawnableInterface::UValorSpawnableInterface(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer)
{

}

void IValorSpawnableInterface::Spawn(APlayerState* UsePlayerState, const FValorVariantData& ExtraData)
{
	unimplemented();
}

void IValorSpawnableInterface::Spawn(APlayerState* UsePlayerState, void* ExtraData)
{
	unimplemented();
}