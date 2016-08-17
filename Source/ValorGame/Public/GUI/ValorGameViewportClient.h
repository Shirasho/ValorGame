// Copyright Shirasho Media 2016. All rights reserved.

#pragma once

#include "ValorGameViewportClient.generated.h"

UCLASS(Within=Engine, Transient, Config=Engine)
class UValorGameViewportClient : public UGameViewportClient
{
    GENERATED_UCLASS_BODY()

public:

	void ReceivedFocus(class FViewport* InViewport) override;

	DECLARE_EVENT(UValorGameViewportClient, FOnReceivedFocus)
	FOnReceivedFocus& OnReceivedFocus()
	{
		return OnReceivedFocusEvent;
	}

private:

	FOnReceivedFocus OnReceivedFocusEvent;
};