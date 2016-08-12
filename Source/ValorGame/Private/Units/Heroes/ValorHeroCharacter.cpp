// Copyright Shirasho Media 2016. All rights reserved.

#include "ValorGame.h"
#include "ValorHeroCharacter.h"

#include "ValorPlayerState.h"

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
		GetCharacterMovement()->bOrientRotationToMovement = true; // Rotate character to moving direction.
		GetCharacterMovement()->RotationRate = FRotator(0.f, 0.f, -1.f); // Instant turning.
		GetCharacterMovement()->bConstrainToPlane = true;
		GetCharacterMovement()->bSnapToPlaneAtStart = true;
		GetCharacterMovement()->SetJumpAllowed(false);
	}
}

void AValorHeroCharacter::BeginPlay()
{
	Super::BeginPlay();

	if (!CharacterDefaults.MainUserInterface)
	{
		UE_LOG(LogValorGUI, Log, TEXT("Character '%s' does not have a MainUserInterface assigned."), *GetNameSafe(this));
	}
	if (!CharacterDefaults.ClickCursorDecal)
	{
		UE_LOG(LogValorGUI, Log, TEXT("Character '%s' does not have a ClickCursorDecal assigned."), *GetNameSafe(this));
	}

	if (GetNetMode() != NM_DedicatedServer)
	{
		if (CharacterDefaults.SpawnParticleTemplate)
		{
			UGameplayStatics::SpawnEmitterAtLocation(this, CharacterDefaults.SpawnParticleTemplate, GetActorLocation(), GetActorRotation());
		}
		if (CharacterDefaults.SpawnSoundCue)
		{
			UGameplayStatics::PlaySoundAtLocation(this, CharacterDefaults.SpawnSoundCue, GetActorLocation());
		}
	}
}

void AValorHeroCharacter::Spawn(APlayerState* UsePlayerState, const FValorVariantData& ExtraData)
{
	if (HasAuthority())
	{
		PlayerState = UsePlayerState ? UsePlayerState : PlayerState;
		Initialize(UsePlayerState);

		// CharacterAI is handled by HeroCharacterProxy due to a required reference
		// for MoveToLocation. Once VG-7 is implemented we can move the remaining
		// controller setup here.
	}
}

void AValorHeroCharacter::GetLifetimeReplicatedProps(TArray< FLifetimeProperty > & OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);

	DOREPLIFETIME(AValorHeroCharacter, CharacterDefaults);
}