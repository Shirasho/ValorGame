// Copyright Shirasho Media 2016. All rights reserved.

#include "ValorGame.h"
#include "ValorGameSession_Classic.h"

#include "Online/ValorOnlineSettings.h"


AValorGameSession_Classic::AValorGameSession_Classic(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer)
{
}

void AValorGameSession_Classic::SetHostSettingsValues(TSharedPtr<class FValorOnlineSessionSettings> Settings, const FString& GameType, const FString& MapName)
{
	Settings->Set(SETTING_GAMEMODE, GameType, EOnlineDataAdvertisementType::ViaOnlineService);
	Settings->Set(SETTING_MAPNAME, MapName, EOnlineDataAdvertisementType::ViaOnlineService);
	Settings->Set(SETTING_MATCHING_HOPPER, FString("Classic"), EOnlineDataAdvertisementType::DontAdvertise);
	Settings->Set(SETTING_MATCHING_TIMEOUT, 120.f, EOnlineDataAdvertisementType::ViaOnlineService);
	Settings->Set(SETTING_SESSION_TEMPLATE_NAME, FString("ValorGameSession_Classic"), EOnlineDataAdvertisementType::DontAdvertise);
	Settings->Set(SEARCH_KEYWORDS, ValorKeywords::CustomMatchKeyword, EOnlineDataAdvertisementType::ViaOnlineService);
}