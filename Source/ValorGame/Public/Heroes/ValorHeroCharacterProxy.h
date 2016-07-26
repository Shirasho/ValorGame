// Copyright Shirasho Media 2016. All rights reserved.

#pragma once

#include "ValorHeroCharacterProxy.generated.h"

class AValorHeroCharacter;

/* This class works as a proxy on the client that tracks the movements of the real 
 * character on the server. This is necessary to work around a known bug regarding 
 * the lack of network functionality for UNavigationSystem::SimpleMoveToLocation(). */
UCLASS(BlueprintType, NotBlueprintable)
class AValorHeroCharacterProxy : public APawn
{
	GENERATED_UCLASS_BODY()

protected:

	/* Top down camera */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera, meta = (AllowPrivateAccess = "true"))
	class UCameraComponent* CameraComponent;

	/* Camera boom positioning the camera above the character */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera, meta = (AllowPrivateAccess = "true"))
	class USpringArmComponent* CameraBoomComponent;

	/* The class of the actual character. */
	TSubclassOf<AValorHeroCharacter> CharacterClass;

	/* The pointer to the actual character. */
	UPROPERTY(Replicated)
	AValorHeroCharacter* Character;

	/* The AI Controller that will auto-navigate the player. */
	class AValorHeroAIController* CharacterAI;

public:

	virtual void BeginPlay() override;

	virtual void PostInitializeComponents() override;

	virtual void Tick(float DeltaSeconds) override;

public:

	/* Called when the player has clicked a valid movement location after the
	 * request has been sent to the server. */
	void OnCharacterMovement();

	/* Used by the AIController to move. */
	void MoveToLocation(const class AValorPlayerController* InController, const FVector& Location);

protected:

	/* Displays the movement decal when the player clicks on a valid movement location. */
	void DisplayMovementDecal();

public:

	AValorHeroCharacter* GetValorHeroCharacter() const;
};