// Copyright Shirasho Media 2016. All rights reserved.

#include "ValorGame.h"
#include "ValorSelectedUnitWidget.h"

void UValorSelectedUnitWidget::NativeConstruct()
{
	Super::NativeConstruct();
}

TSharedRef<SWidget> UValorSelectedUnitWidget::RebuildWidget()
{
	DECLARE_SCOPE_CYCLE_COUNTER(TEXT("UValorSelectedUnitWidget::RebuildWidget"), STAT_ValorSelectedUnitWidget_RebuildWidget, STATGROUP_ValorGUI);

	//@TODO Add root panel component

	return Super::RebuildWidget();
}