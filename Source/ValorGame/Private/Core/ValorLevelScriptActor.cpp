// Copyright Shirasho Media 2016. All rights reserved.

#include "ValorGame.h"
#include "ValorLevelScriptActor.h"

AValorLevelScriptActor::AValorLevelScriptActor(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer)
{
	ValorLevelName = NAME_None;
}