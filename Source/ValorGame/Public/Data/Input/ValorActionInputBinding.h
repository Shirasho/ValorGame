// Copyright Shirasho Media 2016. All rights reserved.

#pragma once

#include "ValorActionInputBinding.generated.h"

USTRUCT(BlueprintType)
struct FValorActionInputBinding
{
	GENERATED_USTRUCT_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Input")
		FString ActionName;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Input")
		FKey Key;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Input")
		FString KeyAsString;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Input")
		bool bShift;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Input")
		bool bCtrl;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Input")
		bool bAlt;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Input")
		bool bCmd;


	FValorActionInputBinding() {}
	FValorActionInputBinding(const FString InActionName, const FKey InKey, const bool bInShift, const bool bInCtrl, const bool bInAlt, const bool bInCmd)
		: Key(InKey)
		, KeyAsString(Key.GetDisplayName().ToString())
		, bShift(bInShift)
		, bCtrl(bInCtrl)
		, bAlt(bInAlt)
		, bCmd(bInCmd)
	{
		ActionName = InActionName;
	}

	FValorActionInputBinding(const FInputActionKeyMapping& Action)
		: Key(Action.Key)
		, KeyAsString(Action.Key.GetDisplayName().ToString())
		, bShift(Action.bShift)
		, bCtrl(Action.bCtrl)
		, bAlt(Action.bAlt)
		, bCmd(Action.bCmd)
	{
		ActionName = Action.ActionName.ToString();
	}
};