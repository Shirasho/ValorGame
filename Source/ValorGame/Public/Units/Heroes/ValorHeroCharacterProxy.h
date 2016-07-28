// Copyright Shirasho Media 2016. All rights reserved.

#pragma once

#include "ValorHeroCharacterProxy.generated.h"

#define VALOR_CAMERA_ORTHO_WIDTH_SCROLL 25.f
#define VALOR_CAMERA_ORTHO_WIDTH_MIN 1250.f
#define VALOR_CAMERA_ORTHO_WIDTH_MAX 1750.f

class AValorHeroCharacter;

/* This class works as a proxy on the client that tracks the movements of the real 
 * character on the server. This is necessary to work around a known bug regarding 
 * the lack of network functionality for UNavigationSystem::SimpleMoveToLocation(). */
UCLASS(BlueprintType, NotBlueprintable, NotPlaceable)
class AValorHeroCharacterProxy : public APawn
{
	GENERATED_UCLASS_BODY()

protected:

	/* Top down camera */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera, meta = (AllowPrivateAccess = "true"))
	UCameraComponent* CameraComponent;

	/* Camera boom positioning the camera above the character */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera, meta = (AllowPrivateAccess = "true"))
	USpringArmComponent* CameraBoomComponent;

	/* The class of the actual character. */
	TSubclassOf<AValorHeroCharacter> CharacterClass;

	/* The pointer to the actual character. */
	UPROPERTY(Replicated)
	AValorHeroCharacter* Character;

	/* The AI Controller that will auto-navigate the player. */
	class AValorHeroAIController* CharacterAI;

private:

	// Camera tracking.
	bool bCenterCamera;

public:

	//virtual void PreInitializeComponents() override;

	virtual void PostInitializeComponents() override;

	virtual void BeginPlay() override;

	//virtual void EndPlay(const EEndPlayReason::Type EndPlayReason) override;

	virtual void Tick(float DeltaSeconds) override;

public:

	/* [Client -> Server] Syncs the player state and initializes the proxy character AI. */
	UFUNCTION(Server, Reliable, WithValidation)
	void ServerCreatePlayer(/*const APlayerState* ControllerPlayerState*/);

	/* Used by the AIController to move. */
	void MoveToLocation(const class AValorPlayerController* InController, const FVector& Location);

public: // PreServer

	void OnCameraCenterPressed();
	void OnCameraCenterReleased();

public: // PostServer

	/* Called when the player has clicked a valid movement location after the
	* request has been sent to the server. */
	void OnCharacterMovement();

protected:

	/* Displays the movement decal when the player clicks on a valid movement location. */
	void DisplayMovementDecal();

public:

	AValorHeroCharacter* GetValorHeroCharacter() const;

	FORCEINLINE UCameraComponent* GetCameraComponent() const
	{
		return CameraComponent;
	}

	FORCEINLINE USpringArmComponent* GetCameraBoomComponent() const
	{
		return CameraBoomComponent;
	}

};