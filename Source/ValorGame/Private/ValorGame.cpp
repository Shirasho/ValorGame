// Copyright 1998-2016 Epic Games, Inc. All Rights Reserved.

#include "ValorGame.h"
#include "AssetRegistryModule.h"
#include "ValorGameDelegates.h"

class FValorGameModule : public FDefaultGameModuleImpl
{
    virtual void StartupModule() override
    {
		InitializeValorGameDelegates();
        FAssetRegistryModule& AssetRegistryModule = FModuleManager::LoadModuleChecked<FAssetRegistryModule>(TEXT("AssetRegistry"));
    }

    virtual void ShutdownModule() override
    {
        
    }
};

IMPLEMENT_PRIMARY_GAME_MODULE(FValorGameModule, ValorGame, "ValorGame");

DEFINE_LOG_CATEGORY(LogValor);
DEFINE_LOG_CATEGORY(LogValorClient);
DEFINE_LOG_CATEGORY(LogValorServer);
DEFINE_LOG_CATEGORY(LogValorHero);