// Copyright Shirasho Media 2016. All rights reserved.

#pragma once

#include "ValorGameSession.h"
#include "ValorGameSession_Classic.generated.h"

UCLASS(Config = Game)
class VALORGAME_API AValorGameSession_Classic : public AValorGameSession
{
	GENERATED_UCLASS_BODY()

protected:

	virtual void SetHostSettingsValues(TSharedPtr<class FValorOnlineSessionSettings> Settings, const FString& GameType, const FString& MapName) override;

public:

	/** Default number of players allowed in a game */
	static const int32 MAX_PLAYERS = 10;
};