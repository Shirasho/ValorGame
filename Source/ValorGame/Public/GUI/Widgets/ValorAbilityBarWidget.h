// Copyright Shirasho Media 2016. All rights reserved.

#pragma once

#include "GUI/ValorUserWidget.h"
#include "ValorAbilityBarWidget.generated.h"

/**
 * 
 */
UCLASS()
class VALORGAME_API UValorAbilityBarWidget : public UValorUserWidget
{
	GENERATED_BODY()
	
public:

	virtual void NativeConstruct() override;
	virtual TSharedRef<SWidget> RebuildWidget() override;	
};
