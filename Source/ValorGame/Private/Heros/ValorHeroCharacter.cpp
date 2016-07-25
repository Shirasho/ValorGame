// Copyright Shirasho Media 2016. All rights reserved.

#include "ValorGame.h"
#include "ValorHeroCharacter.h"


AValorHeroCharacter::AValorHeroCharacter(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer)
{
	if (HasAuthority())
	{
		// Set size for player capsule
		GetCapsuleComponent()->InitCapsuleSize(42.f, 96.0f);

		// Don't rotate character to camera direction
		bUseControllerRotationPitch = false;
		bUseControllerRotationYaw = false;
		bUseControllerRotationRoll = false;

		// Configure character movement
		GetCharacterMovement()->bOrientRotationToMovement = true; // Rotate character to moving direction
		GetCharacterMovement()->RotationRate = FRotator(0.f, 640.f, 0.f);
		GetCharacterMovement()->bConstrainToPlane = true;
		GetCharacterMovement()->bSnapToPlaneAtStart = true;
	}
}

void AValorHeroCharacter::PostInitializeComponents()
{
	Super::PostInitializeComponents();
}

void AValorHeroCharacter::BeginPlay()
{
	Super::BeginPlay();
}

void AValorHeroCharacter::Tick(float DeltaSeconds)
{
	Super::Tick(DeltaSeconds);
}