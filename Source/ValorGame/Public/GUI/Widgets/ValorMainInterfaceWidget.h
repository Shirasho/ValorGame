// Copyright Shirasho Media 2016. All rights reserved.

#pragma once

#include "ValorUserWidget.h"
#include "ValorMainInterfaceWidget.generated.h"

UCLASS()
class UValorMainInterfaceWidget : public UValorUserWidget
{
	GENERATED_BODY()

protected:

	UPROPERTY(BlueprintReadWrite, VisibleAnywhere, Category = Elements)
	class UValorSelectedUnitWidget* SelectedUnitWidget;

public:

	virtual void NativeConstruct() override;
	virtual TSharedRef<SWidget> RebuildWidget() override;

public:

	UFUNCTION(BlueprintCallable, Category = Input)
		void OnAbilityAction1Pressed();

	UFUNCTION(BlueprintCallable, Category = Input)
		void OnAbilityAction1Released();

	UFUNCTION(BlueprintCallable, Category = Input)
		void OnAbilityAction2Pressed();

	UFUNCTION(BlueprintCallable, Category = Input)
		void OnAbilityAction2Released();

	UFUNCTION(BlueprintCallable, Category = Input)
		void OnAbilityAction3Pressed();

	UFUNCTION(BlueprintCallable, Category = Input)
		void OnAbilityAction3Released();

	UFUNCTION(BlueprintCallable, Category = Input)
		void OnAbilityAction4Pressed();

	UFUNCTION(BlueprintCallable, Category = Input)
		void OnAbilityAction4Released();

	UFUNCTION(BlueprintCallable, Category = Input)
		void OnAbilitySpell1Pressed();

	UFUNCTION(BlueprintCallable, Category = Input)
		void OnAbilitySpell1Released();

	UFUNCTION(BlueprintCallable, Category = Input)
		void OnAbilitySpell2Pressed();

	UFUNCTION(BlueprintCallable, Category = Input)
		void OnAbilitySpell2Released();

	UFUNCTION(BlueprintCallable, Category = Input)
		void OnUseItem1Pressed();

	UFUNCTION(BlueprintCallable, Category = Input)
		void OnUseItem2Pressed();

	UFUNCTION(BlueprintCallable, Category = Input)
		void OnUseItem3Pressed();

	UFUNCTION(BlueprintCallable, Category = Input)
		void OnCameraZoomInPressed();

	UFUNCTION(BlueprintCallable, Category = Input)
		void OnCameraZoomOutPressed();

	UFUNCTION(BlueprintCallable, Category = Input)
		void OnCameraCenterPressed();

	UFUNCTION(BlueprintCallable, Category = Input)
		void OnCameraCenterReleased();

	UFUNCTION(BlueprintCallable, Category = Input)
		void OnCameraPanLeftPressed();

	UFUNCTION(BlueprintCallable, Category = Input)
		void OnCameraPanRightPressed();

	UFUNCTION(BlueprintCallable, Category = Input)
		void OnCameraPanUpPressed();

	UFUNCTION(BlueprintCallable, Category = Input)
		void OnCameraPanDownPressed();

	UFUNCTION(BlueprintCallable, Category = Input)
		void OnCameraPanPrecise1Pressed();

	UFUNCTION(BlueprintCallable, Category = Input)
		void OnCameraPanPrecise2Pressed();

	UFUNCTION(BlueprintCallable, Category = Input)
		void OnCameraPanPrecise3Pressed();

	UFUNCTION(BlueprintCallable, Category = Input)
		void OnCameraPanPrecise4Pressed();

	UFUNCTION(BlueprintCallable, Category = Input)
		void OnToggleMenuPressed();

	UFUNCTION(BlueprintCallable, Category = Input)
		void OnToggleScoreboardPressed();

	UFUNCTION(BlueprintCallable, Category = Input)
		void OnPushToTalkPressed();

	UFUNCTION(BlueprintCallable, Category = Input)
		void OnPushToTalkReleased();
};