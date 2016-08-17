// Copyright Shirasho Media 2016. All rights reserved.

#include "ValorGame.h"
#include "ValorUserWidget.h"

void UValorUserWidget::NativeConstruct()
{
	Super::NativeConstruct();
}

TSharedRef<SWidget> UValorUserWidget::RebuildWidget()
{
	DECLARE_SCOPE_CYCLE_COUNTER(TEXT("UValorUserWidget::RebuildWidget"), STAT_ValorUserWidget_RebuildWidget, STATGROUP_ValorGUI);

	return Super::RebuildWidget();
}