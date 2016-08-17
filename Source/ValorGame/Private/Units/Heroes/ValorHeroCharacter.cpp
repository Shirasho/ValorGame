// Copyright Shirasho Media 2016. All rights reserved.

#include "ValorGame.h"
#include "ValorHeroCharacter.h"

#include "ValorPlayerState.h"
#include "ValorHeroAIController.h"

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
		DECLARE_SCOPE_CYCLE_COUNTER(TEXT("AValorHeroCharacter::Spawn"), STAT_ValorHeroCharacter_Spawn, STATGROUP_ValorCharacter);

		PlayerState = UsePlayerState ? UsePlayerState : PlayerState;
		Initialize(UsePlayerState);

		AIController = GetWorld()->SpawnActor<AValorHeroAIController>(GetActorLocation(), GetActorRotation());
		check(AIController);
		AIController->PlayerState = PlayerState;
		AIController->Possess(this);
		if (ensureMsgf(BotBehavior, TEXT("Hero '%s' does not have a BehaviorTree assigned to it. Assign one in the editor."), *GetNameSafe(this)) &&
			ensureMsgf(BotBehavior->BlackboardAsset, TEXT("The BehaviorTree '%s' attached to Minion '%s' does not have a blackboard. Assign one in the editor."), *GetNameSafe(BotBehavior), *GetNameSafe(this)))
		{
			UBlackboardComponent* HeroBlackboardComponent;
			AIController->UseBlackboard(BotBehavior->BlackboardAsset, HeroBlackboardComponent);
			AIController->SetBlackboardComponent(HeroBlackboardComponent);
			AIController->RunBehaviorTree(BotBehavior);
		}
		Controller = AIController;
	}
}

void AValorHeroCharacter::GetLifetimeReplicatedProps(TArray< FLifetimeProperty > & OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);

	DOREPLIFETIME(AValorHeroCharacter, CharacterDefaults);
}