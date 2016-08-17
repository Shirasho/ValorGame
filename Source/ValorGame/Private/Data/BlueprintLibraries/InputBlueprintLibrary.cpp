// Copyright Shirasho Media 2016. All rights reserved.

#include "ValorGame.h"
#include "InputBlueprintLibrary.h"


void UInputBlueprintLibrary::K2_GetAxisAndActionMappingsForKey(FKey Key, TArray<FValorActionInputBinding>& ActionBindings, TArray<FValorAxisInputBinding>& AxisBindings)
{
	ActionBindings.Empty();
	AxisBindings.Empty();

	const UInputSettings* Settings = GetDefault<UInputSettings>();
	if (!Settings)
	{
		return;
	}

	const TArray<FInputActionKeyMapping>& ActionMappings = Settings->ActionMappings;

	for (const FInputActionKeyMapping& ActionKeyMapping : ActionMappings)
	{
		if (ActionKeyMapping.Key == Key)
		{
			ActionBindings.Add(FValorActionInputBinding(ActionKeyMapping));
		}
	}

	const TArray<FInputAxisKeyMapping>& AxisMappings = Settings->AxisMappings;

	for (const FInputAxisKeyMapping& AxisKeyMapping : AxisMappings)
	{
		if (AxisKeyMapping.Key == Key)
		{
			AxisBindings.Add(FValorAxisInputBinding(AxisKeyMapping));
		}
	}
}

FValorAxisInputBinding UInputBlueprintLibrary::K2_GetInputAxis(const FKeyEvent& KeyEvent)
{
	FValorAxisInputBinding Binding;
	
	Binding.Key = KeyEvent.GetKey();
	Binding.KeyAsString = Binding.Key.GetDisplayName().ToString();

	Binding.Scale = 1;

	return Binding;
}

void UInputBlueprintLibrary::K2_GetAllAxisKeyBindings(TArray<FValorAxisInputBinding>& Bindings)
{
	Bindings.Empty();

	const UInputSettings* Settings = GetDefault<UInputSettings>();
	if (!Settings)
	{
		return;
	}

	const TArray<FInputAxisKeyMapping>& AxisMappings = Settings->AxisMappings;
	for (const FInputAxisKeyMapping& AxisKeyMapping : AxisMappings)
	{
		Bindings.Add(FValorAxisInputBinding(AxisKeyMapping));
	}
}

void UInputBlueprintLibrary::K2_RemoveAxisKeyBinding(FValorAxisInputBinding BindingToRemove)
{
	UInputSettings* Settings = GetMutableDefault<UInputSettings>();
	if (!Settings)
	{
		return;
	}

	TArray<FInputAxisKeyMapping>& AxisMappings = Settings->AxisMappings;

	bool bFound = false;
	for (int32 Index = 0; Index < AxisMappings.Num(); ++Index)
	{
		if (AxisMappings[Index].Key == BindingToRemove.Key)
		{
			bFound = true;
			AxisMappings.RemoveAt(Index);
			Index = 0;
		}
	}

	if (bFound)
	{
		Settings->SaveKeyMappings();

		for (TObjectIterator<UPlayerInput> It; It; ++It)
		{
			It->ForceRebuildingKeyMaps(true);
		}
	}
}

bool UInputBlueprintLibrary::K2_RebindAxisKey(FValorAxisInputBinding OriginalBinding, FValorAxisInputBinding NewBinding)
{
	UInputSettings* Settings = const_cast<UInputSettings*>(GetDefault<UInputSettings>());
	if (!Settings)
	{
		return false;
	}

	TArray<FInputAxisKeyMapping>& AxisMappings = Settings->AxisMappings;

	bool bFound = false;
	for (FInputAxisKeyMapping& AxisKeyMapping : AxisMappings)
	{
		if (AxisKeyMapping.AxisName.ToString() == OriginalBinding.AxisName && AxisKeyMapping.Key == OriginalBinding.Key)
		{
			UpdateAxisMapping(AxisKeyMapping, NewBinding);
			bFound = true;
			break;
		}
	}

	if (bFound)
	{
		const_cast<UInputSettings*>(Settings)->SaveKeyMappings();

		for (TObjectIterator<UPlayerInput> It; It; ++It)
		{
			It->ForceRebuildingKeyMaps(true);
		}
	}
	return bFound;
}

FValorActionInputBinding UInputBlueprintLibrary::K2_GetInputAction(const FKeyEvent& KeyEvent)
{
	FValorActionInputBinding Binding;

	Binding.Key = KeyEvent.GetKey();
	Binding.KeyAsString = Binding.Key.GetDisplayName().ToString();

	Binding.bAlt = KeyEvent.IsAltDown();
	Binding.bCtrl = KeyEvent.IsControlDown();
	Binding.bShift = KeyEvent.IsShiftDown();
	Binding.bCmd = KeyEvent.IsCommandDown();

	return Binding;
}

void UInputBlueprintLibrary::K2_GetAllActionKeyBindings(TArray<FValorActionInputBinding>& Bindings)
{
	Bindings.Empty();

	const UInputSettings* Settings = GetDefault<UInputSettings>();
	if (!Settings)
	{
		return;
	}

	const TArray<FInputActionKeyMapping>& ActionMappings = Settings->ActionMappings;
	for (const FInputActionKeyMapping& ActionKeyMapping : ActionMappings)
	{
		Bindings.Add(FValorActionInputBinding(ActionKeyMapping));
	}
}

void UInputBlueprintLibrary::K2_RemoveActionKeyBinding(FValorActionInputBinding BindingToRemove)
{
	UInputSettings* Settings = GetMutableDefault<UInputSettings>();
	if (!Settings)
	{
		return;
	}

	TArray<FInputActionKeyMapping>& ActionMappings = Settings->ActionMappings;

	bool bFound = false;
	for (int32 Index = 0; Index < ActionMappings.Num(); ++Index)
	{
		if (ActionMappings[Index].Key == BindingToRemove.Key)
		{
			bFound = true;
			ActionMappings.RemoveAt(Index);
			Index = 0;
		}
	}

	if (bFound)
	{
		Settings->SaveKeyMappings();

		for (TObjectIterator<UPlayerInput> It; It; ++It)
		{
			It->ForceRebuildingKeyMaps(true);
		}
	}
}

bool UInputBlueprintLibrary::K2_RebindActionKey(FValorActionInputBinding OriginalBinding, FValorActionInputBinding NewBinding)
{
	UInputSettings* Settings = const_cast<UInputSettings*>(GetDefault<UInputSettings>());
	if (!Settings)
	{
		return false;
	}

	TArray<FInputActionKeyMapping>& ActionMappings = Settings->ActionMappings;

	bool bFound = false;
	for (FInputActionKeyMapping& ActionKeyMapping : ActionMappings)
	{
		if (ActionKeyMapping.ActionName.ToString() == OriginalBinding.ActionName && ActionKeyMapping.Key == OriginalBinding.Key)
		{
			UpdateActionMapping(ActionKeyMapping, NewBinding);
			bFound = true;
			break;
		}
	}

	if (bFound)
	{
		const_cast<UInputSettings*>(Settings)->SaveKeyMappings();

		for (TObjectIterator<UPlayerInput> It; It; ++It)
		{
			It->ForceRebuildingKeyMaps(true);
		}
	}
	return bFound;
}