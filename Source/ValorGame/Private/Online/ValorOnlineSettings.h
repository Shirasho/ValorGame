// Copyright Shirasho Media 2016. All rights reserved.

#pragma once

#include "Online.h"

// General settings for a game.
class FValorOnlineSessionSettings : public FOnlineSessionSettings
{
public:

    FValorOnlineSessionSettings(bool bIsLAN = false, bool bIsPresence = false, int32 MaxNumPlayers = 4);
    virtual ~FValorOnlineSessionSettings() {}
};

// General search settings for game.
class FValorOnlineSearchSettings : public FOnlineSessionSearch
{
public:
    FValorOnlineSearchSettings(bool bSearchingLAN = false, bool bSearchingPresence = false);
    virtual ~FValorOnlineSearchSettings() {}
};

// Search settings for an empty dedicated server to host a match.
class FValorOnlineSearchSettingsEmptyDedicated : public FValorOnlineSearchSettings
{
public:
    FValorOnlineSearchSettingsEmptyDedicated(bool bSearchingLAN = false, bool bSearchingPresence = false);
    virtual ~FValorOnlineSearchSettingsEmptyDedicated() {}
};