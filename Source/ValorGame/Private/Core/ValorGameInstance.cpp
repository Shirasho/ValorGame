// Copyright Shirasho Media 2016. All rights reserved.

#include "ValorGame.h"
#include "ValorGameInstance.h"


namespace ValorGameState
{
    const FName None = FName(TEXT("None"));
    const FName PendingInvite = FName(TEXT("PendingInvite"));
    const FName WelcomeScreen = FName(TEXT("WelcomeScreen"));
    const FName MainMenu = FName(TEXT("MainMenu"));
    const FName MessageMenu = FName(TEXT("MessageMenu"));
    const FName Playing = FName(TEXT("Playing"));
}

UValorGameInstance::UValorGameInstance(const FObjectInitializer& ObjectInitializer)
    : Super(ObjectInitializer)
{
    
}