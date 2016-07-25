// Copyright Shirasho Media 2016. All rights reserved.

#pragma once

#include "ValorInventoryItemEffectInterface.h"
#include "ValorInventoryItemStatTableRow.h"
#include "ValorInventoryItem.generated.h"

USTRUCT(Blueprintable, BlueprintType)
struct FValorInventoryItem
{
	GENERATED_USTRUCT_BODY()

public:

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Stats)
	FDataTableRowHandle ItemStatInformation;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Stats)
	TScriptInterface<IValorInventoryItemEffectInterface> ItemEffectInterface;

	FValorInventoryItem()
	{
		/* Only perform check in development builds. */
		checkCode(
			if (ItemStatInformation.DataTable)
			{
				ensure(ItemStatInformation.DataTable->RowStruct->IsChildOf(FValorInventoryItemStatTableRow::StaticStruct()));
			}
			//ensure(ItemStatInformation.DataTable);
			//ensure(ItemStatInformation.RowName != NAME_None);
		);
	}
};