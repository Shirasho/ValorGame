// Copyright Shirasho Media 2016. All rights reserved.

#pragma once

#include "ValorPlayerController.generated.h"

UCLASS(Config = Game)
class AValorPlayerController : public APlayerController
{

    GENERATED_UCLASS_BODY()

protected:

	/* The UValorMainInterfaceWidget to use as the main GUI. */
	class UValorMainInterfaceWidget* MainUserInterface;

private:

	/* Timer used to keep attempting to start an online game until it works. */
	FTimerHandle TimerHandle_ClientStartOnlineGame;

	/* Timer used for movement when holding the action button down. */
	FTimerHandle TimerHandle_MoveToCursor;

	/* Timer used for init-ing GUI at start. Since proxy character 
	 * possession happens on BeginPlay() there is no guarantee that 
	 * ValorPlayerController::BeginPlay() will be called after the proxy 
	 * character is ready. In this case we just set a timer that goes
	 * until the ProxyCharacter is valid. */
	FTimerHandle TimerHandle_InitUserProperties;

public:

	//virtual void PreInitializeComponents() override;

	virtual void PostInitializeComponents() override;

	virtual void BeginPlay() override;

	virtual void EndPlay(const EEndPlayReason::Type EndPlayReason) override;

	virtual void Tick(float DeltaSeconds) override;

    virtual void SetupInputComponent() override;

public:

	UFUNCTION(BlueprintPure, Category=Character)
	class AValorHeroCharacterProxy* GetValorHeroCharacterProxy() const;

	class AValorHeroCharacter* GetValorHeroCharacter() const;

public:

	/* [Server -> Client] Starts the online game using the session name specified in the PlayerState. */
	UFUNCTION(Client, Reliable)
	void ClientStartOnlineMatch();

	/* [Server -> Client] Ends the online game using the session name specified in the PlayerState. */
	UFUNCTION(Client, Reliable)
	void ClientEndOnlineMatch();

public:

	/* [Client -> Server] Sends a cheat message to the server. */
	UFUNCTION(Server, Reliable, WithValidation)
	void ServerCheat(const FString& Message);

protected:

	/* [Client -> Server] Asks the server to move the player to the specified location. */
	UFUNCTION(Server, Reliable, WithValidation)
	void ServerMoveToCursor(const FHitResult& HitResult);

	/* [Server] Move the player to the specified location. */
	void MoveToCursor(const FHitResult& HitResult);

public:

	UFUNCTION(BlueprintCallable, Category = Input)
    void OnPrimaryAction1Pressed();

	UFUNCTION(BlueprintCallable, Category = Input)
    void OnPrimaryAction1Released();

	UFUNCTION(BlueprintCallable, Category = Input)
    void OnPrimaryAction2Pressed();

	UFUNCTION(BlueprintCallable, Category = Input)
    void OnPrimaryAction2Released();

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
    void OnCameraPanLeftReleased();

	UFUNCTION(BlueprintCallable, Category = Input)
    void OnCameraPanRightPressed();

	UFUNCTION(BlueprintCallable, Category = Input)
    void OnCameraPanRightReleased();

	UFUNCTION(BlueprintCallable, Category = Input)
    void OnCameraPanUpPressed();

	UFUNCTION(BlueprintCallable, Category = Input)
    void OnCameraPanUpReleased();

	UFUNCTION(BlueprintCallable, Category = Input)
    void OnCameraPanDownPressed();

	UFUNCTION(BlueprintCallable, Category = Input)
    void OnCameraPanDownReleased();

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

private:

	void OnWindowReceivedFocus();

	/* Needed to ensure the PlayerProxy is created. */
	void ValorInitCharacter();

	UFUNCTION(Client, Reliable)
	void ClientValorInitUserInterface();
};