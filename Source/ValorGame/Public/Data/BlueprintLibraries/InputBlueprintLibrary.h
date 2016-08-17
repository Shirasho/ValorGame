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

	UFUNCTION(BlueprintPure, Category = "Input|Key Rebinding", DisplayName = "Get Axis and Action Mappings for Key")
		static void K2_GetAxisAndActionMappingsForKey(FKey Key, TArray<FValorActionInputBinding>& ActionBindings, TArray<FValorAxisInputBinding>& AxisBindings);


	UFUNCTION(BlueprintPure, Category = "Input|Key Rebinding", DisplayName = "Get Input Axis")
		static FValorAxisInputBinding K2_GetInputAxis(const FKeyEvent& KeyEvent);

	UFUNCTION(BlueprintPure, Category = "Input|Key Rebinding", DisplayName = "Get All Axis Key Bindings")
		static void K2_GetAllAxisKeyBindings(TArray<FValorAxisInputBinding>& Bindings);

	UFUNCTION(BlueprintCallable, Category = "Input|Key Rebinding", DisplayName = "Remove Axis Key Binding")
		static void K2_RemoveAxisKeyBinding(FValorAxisInputBinding BindingToRemove);

	UFUNCTION(BlueprintCallable, Category = "Input|Key Rebinding", DisplayName = "Rebind Axis Key Binding")
		static bool K2_RebindAxisKey(FValorAxisInputBinding OriginalBinding, FValorAxisInputBinding NewBinding);


	UFUNCTION(BlueprintPure, Category = "Input|Key Rebinding", DisplayName = "Get Input Action")
		static FValorActionInputBinding K2_GetInputAction(const FKeyEvent& KeyEvent);

	UFUNCTION(BlueprintPure, Category = "Input|Key Rebinding", DisplayName = "Get All Action Key Bindings")
		static void K2_GetAllActionKeyBindings(TArray<FValorActionInputBinding>& Bindings);

	UFUNCTION(BlueprintCallable, Category = "Input|Key Rebinding", DisplayName = "Remove Action Key Binding")
		static void K2_RemoveActionKeyBinding(FValorActionInputBinding BindingToRemove);

	UFUNCTION(BlueprintCallable, Category = "Input|Key Rebinding", DisplayName = "Rebind Action Key Binding")
		static bool K2_RebindActionKey(FValorActionInputBinding OriginalBinding, FValorActionInputBinding NewBinding);

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