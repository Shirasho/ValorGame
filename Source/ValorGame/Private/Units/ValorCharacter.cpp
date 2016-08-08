// Copyright Shirasho Media 2016. All rights reserved.

#include "ValorGame.h"
#include "ValorCharacter.h"

#include "ValorCollisionDefinitions.h"

#include "ValorPlayerState.h"
#include "ValorLaneMinion.h"
#include "ValorCharacter.h"
#include "ValorHeroAIController.h"
#include "ValorMinionController.h"

#include "ValorUnitStatComponent.h"

AValorCharacter::AValorCharacter(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer)
{
	if (HasAuthority())
	{
		AbilityHitbox = CreateDefaultSubobject<UCapsuleComponent>(TEXT("AbilityHitbox"));
		AbilityHitbox->InitCapsuleSize(42.f, 96.0f);
		AbilityHitbox->SetCollisionProfileName(TEXT(VALOR_COLLISION_TRACE_PRESET_1));
		AbilityHitbox->SetNetAddressable();
		AbilityHitbox->SetIsReplicated(true);
		AbilityHitbox->CanCharacterStepUpOn = ECB_No;
		AbilityHitbox->bCheckAsyncSceneOnMove = false;
		AbilityHitbox->bDynamicObstacle = true;
		AbilityHitbox->bGenerateOverlapEvents = true;
		AbilityHitbox->ShapeColor = FColor::Yellow;
		AbilityHitbox->SetupAttachment(RootComponent);

		GetMovementComponent()->SetJumpAllowed(false);
		
		GetMesh()->SetCollisionEnabled(ECollisionEnabled::NoCollision);
		GetMesh()->UpdateCollisionProfile();

		UCharacterMovementComponent* MovementComponent = Cast<UCharacterMovementComponent>(GetMovementComponent());
		if (MovementComponent)
		{
			MovementComponent->RotationRate = FRotator(0.f, 0.f, 750.f);
			MovementComponent->bRequestedMoveUseAcceleration = false;
			MovementComponent->GroundFriction = 0.f;
		}

		CharacterTeam = EValorTeam::None;
	}

	bReplicates = true;
}

float AValorCharacter::TakeDamage(float DamageAmount, FDamageEvent const& DamageEvent, AController* EventInstigator, AActor* DamageCauser)
{
	// Blackboard keys.
	static FName HeroAggroRange(TEXT("AggroHeroRange"));
	static FName MinionAggroRange(TEXT("AggroMinionRange"));
	static FName EnemyMinionActor(TEXT("EnemyMinionActor"));
	static FName EnemyHeroActor(TEXT("EnemyHeroActor"));
	static FName AggroPoint(TEXT("AggroPoint"));

	if (HasAuthority())
	{
		if (!bDamageable)
		{
			return Super::TakeDamage(0.f, DamageEvent, EventInstigator, DamageCauser);
		}

		bool bKilledUnit = false;

		//@TODO Calculate actual damage.


		/*** We want to set some blackboard variables depending on some conditions. ***/

		const AValorCharacter* OtherAsValorCharacter = Cast<AValorCharacter>(DamageCauser);

		// If the other character is not a ValorCharacter (turret damage for example),
		// none of this applies.
		if (OtherAsValorCharacter)
		{
			const AValorHeroCharacter* ThisAsHero = Cast<AValorHeroCharacter>(this);
			const AValorHeroCharacter* OtherAsHero = Cast<AValorHeroCharacter>(DamageCauser);
			const AValorLaneMinion* ThisAsMinion = Cast<AValorLaneMinion>(this);
			const AValorLaneMinion* OtherAsMinion = Cast<AValorLaneMinion>(DamageCauser);

			const bool bIsHeroToHero = ThisAsHero && OtherAsHero;
			const bool bIsHeroToMinion = ThisAsMinion && OtherAsHero;
			const bool bIsMinionToHero = ThisAsHero && OtherAsMinion;
			const bool bIsMinionToMinion = ThisAsMinion && OtherAsMinion;

			// For every lane minion that exists...
			for (TActorIterator<AValorLaneMinion> It(GetWorld()); It; ++It)
			{
				AValorLaneMinion* Minion = *It;
				if (Minion->IsValidLowLevel() && Minion->IsAlive() && !Minion->IsPendingKill() && OtherAsValorCharacter && (Minion->GetTeam() != OtherAsValorCharacter->GetTeam()))
				{
					AValorMinionController* MinionController = Cast<AValorMinionController>(Minion->GetController());
					// If the minion is fully valid...
					if (MinionController && MinionController->GetBlackboardComponent())
					{
						FName AggroBlackboardKey = (bIsHeroToHero || bIsHeroToMinion) ? HeroAggroRange : MinionAggroRange;
						// Get the aggro range of the minion and the distance from the damaged actor to the minion.
						const float AggroRange = MinionController->GetBlackboardComponent()->GetValueAsFloat(AggroBlackboardKey);
						const float Distance = FVector::Dist(GetActorLocation(), Minion->GetActorLocation());

						if (Distance <= AggroRange)
						{
							FName ActorBlackboardKey = (bIsHeroToHero || bIsHeroToMinion) ? EnemyHeroActor : EnemyMinionActor;
							// Set the appropriate taret actor, only overwriting the actor if one doesn't exist already (this is reset in the behavior tree).
							if (!MinionController->GetBlackboardComponent()->GetValueAsObject(ActorBlackboardKey))
							{
								MinionController->GetBlackboardComponent()->SetValueAsObject(ActorBlackboardKey, DamageCauser);
							}

							// Set the appropriate aggro point if it is not already set (this is reset in behavior tree).
							if (MinionController->GetBlackboardComponent()->GetValueAsVector(AggroPoint).IsZero())
							{
								MinionController->GetBlackboardComponent()->SetValueAsVector(AggroPoint, Minion->GetActorLocation());
							}
						}
					}
				}
			}
		}

		// Server-side OnDamageTaken is handled above.

		// Call client-side, interested party OnDamageTaken.
		ClientOnDamageTaken(DamageAmount, bKilledUnit, DamageEvent, DamageCauser);
		// Call client-side, all party OnDamageTaken.
		MulticastOnDamageTaken(DamageAmount, bKilledUnit, DamageEvent, DamageCauser);

		return Super::TakeDamage(DamageAmount, DamageEvent, EventInstigator, DamageCauser);
	}

	return 0.f;
}

void AValorCharacter::OnDamageTaken_Implementation(float DamageAmount, bool bKilledUnit, FDamageEvent const& DamageEvent, AActor* DamageCauser)
{

}

void AValorCharacter::ClientOnDamageTaken_Implementation(float DamageAmount, bool bKilledUnit, FDamageEvent const& DamageEvent, AActor* DamageCauser)
{
	// Interested party events.
}

void AValorCharacter::MulticastOnDamageTaken_Implementation(float DamageAmount, bool bKilledUnit, FDamageEvent const& DamageEvent, AActor* DamageCauser)
{
	if (GetNetMode() != NM_DedicatedServer)
	{
		// Draw the damage to all user HUDs.

		// Call blueprint OnDamageTaken. Draw the damage to all user HUDs and play animations.
		OnDamageTaken(DamageAmount, bKilledUnit, DamageEvent, DamageCauser);
	}
}

bool AValorCharacter::IsEnemyOf(const AValorCharacter* OtherCharacter) const
{
	/* Null characters or the player itself are not enemies. */
	if (!OtherCharacter || OtherCharacter->Controller == Controller)
	{
		return false;
	}

	const AValorPlayerState* MyPlayerState = Cast<AValorPlayerState>(PlayerState);
	const AValorPlayerState* OtherPlayerState = Cast<AValorPlayerState>(OtherCharacter->PlayerState);

	bool bEnemy = false;
	if (MyPlayerState && OtherPlayerState)
	{
		bEnemy = MyPlayerState->IsEnemyOf(OtherPlayerState);
	}

	return bEnemy;
}


EValorTeam AValorCharacter::GetTeam() const
{
	const AValorPlayerState* MyPlayerState = Cast<AValorPlayerState>(PlayerState);
	if (MyPlayerState)
	{
		/* Ensure this character's team is up to date with the PlayerState.
		 * Since this is a const method we need a mutable instance. */
		AValorCharacter* MutableThis = const_cast<AValorCharacter*>(this);
		MutableThis->CharacterTeam = MyPlayerState->GetPlayerTeam();
	}
	return CharacterTeam;
}

bool AValorCharacter::IsAlive() const
{
	bool bAlive = IsValidLowLevel();
	return bAlive && (GetStatComponent() ? StatComponent->GetHealth(EValorStatType::Current) > 0 : true);
}

void AValorCharacter::Initialize(class APlayerState* InPlayerState)
{
	if (HasAuthority())
	{
		PlayerState = InPlayerState;
		if (GetStatComponent())
		{
			StatComponent->Initialize(Cast<AValorPlayerState>(InPlayerState));
		}
	}
}

UValorStatComponent* AValorCharacter::GetStatComponent() const
{
	if (StatComponent)
	{
		return StatComponent;
	}

	/* Mutable instance of this to work around const. */
	AValorCharacter* MutableThis = const_cast<AValorCharacter*>(this);
	return MutableThis->StatComponent = FindComponentByClass<UValorStatComponent>();
}

void AValorCharacter::OnLevelUp()
{
	//StatComponent->RecalculateStats(false, true);
}

float AValorCharacter::PlayAnimMontage(class UAnimMontage* AnimMontage, float InPlayRate, FName StartSectionName)
{
	USkeletalMeshComponent* UseMesh = GetMesh();
	if (AnimMontage && UseMesh && UseMesh->AnimScriptInstance)
	{
		return UseMesh->AnimScriptInstance->Montage_Play(AnimMontage, InPlayRate);
	}

	return 0.0f;
}

void AValorCharacter::StopAnimMontage(class UAnimMontage* AnimMontage)
{
	USkeletalMeshComponent* UseMesh = GetMesh();
	if (AnimMontage && UseMesh && UseMesh->AnimScriptInstance &&
		UseMesh->AnimScriptInstance->Montage_IsPlaying(AnimMontage))
	{
		UseMesh->AnimScriptInstance->Montage_Stop(AnimMontage->BlendOut.GetBlendTime());
	}
}

void AValorCharacter::StopAllAnimMontages()
{
	USkeletalMeshComponent* UseMesh = GetMesh();
	if (UseMesh && UseMesh->AnimScriptInstance)
	{
		UseMesh->AnimScriptInstance->Montage_Stop(0.0f);
	}
}


void AValorCharacter::GetLifetimeReplicatedProps(TArray< FLifetimeProperty > & OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);

	DOREPLIFETIME(AValorCharacter, CharacterTeam); // Mostly here for minions - player's team will properly replicate through PlayerState.
	DOREPLIFETIME(AValorCharacter, bTargetable);
	DOREPLIFETIME(AValorCharacter, bDamageable);
}