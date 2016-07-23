// Copyright Shirasho Media 2016. All rights reserved.

#pragma once

#include "ValorCharacterStatContainer.h"
#include "ValorPlayerController.generated.h"

UCLASS(Config = Game)
class AValorPlayerController : public APlayerController
{

    GENERATED_UCLASS_BODY()

private:

	/* Timer used to keep attempting to start an online game until it works. */
	FTimerHandle TimerHandle_ClientStartOnlineGame;

	/* Timer used for movement when holding the action button down. */
	FTimerHandle TimerHandle_MoveToCursor;

protected:

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

protected:

    void OnPrimaryAction1Pressed();

    void OnPrimaryAction1Released();

    void OnPrimaryAction2Pressed();

    void OnPrimaryAction2Released();

    void OnAbilityAction1Pressed();

    void OnAbilityAction1Released();

    void OnAbilityAction2Pressed();

    void OnAbilityAction2Released();

    void OnAbilityAction3Pressed();

    void OnAbilityAction3Released();

    void OnAbilityAction4Pressed();

    void OnAbilityAction4Released();

    void OnAbilitySpell1Pressed();

    void OnAbilitySpell1Released();

    void OnAbilitySpell2Pressed();

    void OnAbilitySpell2Released();

    void OnUseItem1Pressed();

    void OnUseItem2Pressed();

    void OnUseItem3Pressed();

    void OnCameraZoomInPressed();

    void OnCameraZoomOutPressed();

    void OnCameraCenterPressed();

    void OnCameraPanLeftPressed();

    void OnCameraPanLeftReleased();

    void OnCameraPanRightPressed();

    void OnCameraPanRightReleased();

    void OnCameraPanUpPressed();

    void OnCameraPanUpReleased();

    void OnCameraPanDownPressed();

    void OnCameraPanDownReleased();

    void OnCameraPanPrecise1Pressed();

    void OnCameraPanPrecise2Pressed();

    void OnCameraPanPrecise3Pressed();

    void OnCameraPanPrecise4Pressed();

    void OnToggleMenuPressed();

    void OnToggleScoreboardPressed();

    void OnPushToTalkPressed();

    void OnPushToTalkReleased();
};