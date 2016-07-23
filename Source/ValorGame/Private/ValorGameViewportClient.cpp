// Copyright Shirasho Media 2016. All rights reserved.

#include "ValorGame.h"
#include "ValorGameViewportClient.h"

UValorGameViewportClient::UValorGameViewportClient(const FObjectInitializer& ObjectInitializer)
    : Super(ObjectInitializer)
{
    // Suppress default engine behavior of adding text to
    // the screen that displays when the game is transitioning.
    SetSuppressTransitionMessage(true);
}