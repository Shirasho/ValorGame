// Copyright Shirasho Media 2016. All rights reserved.

#include "ValorGame.h"
#include "ValorAbilityBarWidget.h"

void UValorAbilityBarWidget::NativeConstruct()
{
	Super::NativeConstruct();
}

TSharedRef<SWidget> UValorAbilityBarWidget::RebuildWidget()
{
	DECLARE_SCOPE_CYCLE_COUNTER(TEXT("UValorMainInterfaceWidget::RebuildWidget"), STAT_ValorMainInterfaceWidget_RebuildWidget, STATGROUP_ValorGUI);

	TSharedRef<SWidget> Widget = Super::RebuildWidget();
	UPanelWidget* RootWidget = Cast<UPanelWidget>(GetRootWidget());

	//@TODO Add root panel component

	if (RootWidget && WidgetTree)
	{
		
	}

	return Widget;
}