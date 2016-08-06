// Copyright Shirasho Media 2016. All rights reserved.
// Adapted from Rama's Victory Plugin (https://github.com/EverNewJoy/VictoryPlugin)

#pragma once

#include "ValorActionInputBinding.h"
#include "ValorAxisInputBinding.h"
#include "InputBlueprintLibrary.generated.h"

UCLASS()
class UInputBlueprintLibrary : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()

public:

	UFUNCTION(BlueprintPure, Category = "Input|Key Rebinding")
		static void GetAxisAndActionMappingsForKey(FKey Key, TArray<FValorActionInputBinding>& ActionBindings, TArray<FValorAxisInputBinding>& AxisBindings);


	UFUNCTION(BlueprintPure, Category = "Input|Key Rebinding")
		static FValorAxisInputBinding GetInputAxis(const FKeyEvent& KeyEvent);

	UFUNCTION(BlueprintPure, Category = "Input|Key Rebinding")
		static void GetAllAxisKeyBindings(TArray<FValorAxisInputBinding>& Bindings);

	UFUNCTION(BlueprintCallable, Category = "Input|Key Rebinding")
		static void RemoveAxisKeyBinding(FValorAxisInputBinding BindingToRemove);

	UFUNCTION(BlueprintCallable, Category = "Input|Key Rebinding")
		static bool RebindAxisKey(FValorAxisInputBinding OriginalBinding, FValorAxisInputBinding NewBinding);


	UFUNCTION(BlueprintPure, Category = "Input|Key Rebinding")
		static FValorActionInputBinding GetInputAction(const FKeyEvent& KeyEvent);

	UFUNCTION(BlueprintPure, Category = "Input|Key Rebinding")
		static void GetAllActionKeyBindings(TArray<FValorActionInputBinding>& Bindings);

	UFUNCTION(BlueprintCallable, Category = "Input|Key Rebinding")
		static void RemoveActionKeyBinding(FValorActionInputBinding BindingToRemove);

	UFUNCTION(BlueprintCallable, Category = "Input|Key Rebinding")
		static bool RebindActionKey(FValorActionInputBinding OriginalBinding, FValorActionInputBinding NewBinding);

public:

	static FORCEINLINE void UpdateAxisMapping(FInputAxisKeyMapping& Destination, const FValorAxisInputBinding& NewInput)
	{
		Destination.Key = NewInput.Key;
		Destination.Scale = NewInput.Scale;
	}

	static FORCEINLINE void UpdateActionMapping(FInputActionKeyMapping& Destination, const FValorActionInputBinding& NewInput)
	{
		Destination.Key = NewInput.Key;
		Destination.bShift = NewInput.bShift;
		Destination.bCtrl = NewInput.bCtrl;
		Destination.bAlt = NewInput.bAlt;
		Destination.bCmd = NewInput.bCmd;
	}
};