// Copyright Shirasho Media 2016. All rights reserved.

#pragma once

#include "ValorUserWidget.h"
#include "ValorSelectedUnitWidget.generated.h"

UCLASS()
class UValorSelectedUnitWidget : public UUserWidget
{
	GENERATED_BODY()

public:

	virtual void NativeConstruct() override;
	virtual TSharedRef<SWidget> RebuildWidget() override;
};