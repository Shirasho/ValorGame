// Copyright Shirasho Media 2016. All rights reserved.

#include "ValorGame.h"
#include "ValorCharacter.h"

#include "ValorCollisionDefinitions.h"

#include "ValorPlayerstate.h"


AValorCharacter::AValorCharacter(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer)
{
	if (HasAuthority())
	{
		/* Collision hitbox. */
		//GetCapsuleComponent()->InitCapsuleSize(42.f, 96.0f);
		//GetCapsuleComponent()->SetCollisionProfileName(TEXT(VALOR_COLLISION_TRACE_PRESET_1));
		//GetCapsuleComponent()->CanCharacterStepUpOn = ECB_No;
		//GetCapsuleComponent()->ShapeColor = FColor::Green;
		////GetCapsuleComponent()->bShouldUpdatePhysicsVolume = true;
		//GetCapsuleComponent()->bCheckAsyncSceneOnMove = false;
		//GetCapsuleComponent()->bDynamicObstacle = true;
		//GetCapsuleComponent()->bGenerateOverlapEvents = true;

		//CharacterHitbox = CreateDefaultSubobject<UCapsuleComponent>(TEXT("CharacterHitbox"));
		//CharacterHitbox->InitCapsuleSize(42.f, 96.0f);
		//CharacterHitbox->SetCollisionProfileName(TEXT(VALOR_COLLISION_TRACE_PRESET_2));
		//CharacterHitbox->CanCharacterStepUpOn = ECB_No;
		//CharacterHitbox->ShapeColor = FColor::Blue;
		//CharacterHitbox->SetCanEverAffectNavigation(true);
		//CharacterHitbox->bShouldUpdatePhysicsVolume = true;
		//CharacterHitbox->bCheckAsyncSceneOnMove = false;
		//CharacterHitbox->bDynamicObstacle = true;
		//CharacterHitbox->bGenerateOverlapEvents = true;
		//CharacterHitbox->SetupAttachment(RootComponent);

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
	}

	UCharacterMovementComponent* MovementComponent = Cast<UCharacterMovementComponent>(GetMovementComponent());
	if (MovementComponent)
	{
		MovementComponent->RotationRate = FRotator(0.f, 0.f, -1.f);
		MovementComponent->bRequestedMoveUseAcceleration = false;
		MovementComponent->GroundFriction = 0.f;
	}

	bReplicates = true;
}

void AValorCharacter::PostInitializeComponents()
{
	Super::PostInitializeComponents();

	if (HasAuthority())
	{
		Health = GetMaxHealth();
		PrimaryResource = GetMaxPrimaryResource();

		/* Default to leaving the secondary resource empty.
		 * Individual heros can override this in their
		 * PostInitializeComponents(). */
		SecondaryResource = GetMaxSecondaryResource();

		if (ensureMsgf(StatInformation.DataTable, TEXT("A ValorCharacterStatTableRow has not been assigned for character '%s'. Please assign one in the editor."), *GetName()) &&
			ensureMsgf(StatInformation.RowName != NAME_None, TEXT("A row of 'None' has been assigned for character '%s' as their StatInformation row. Please assign a valid row in the editor."), *GetName()))
		{
			BaseHealth = StatInformation.GetRow<FValorCharacterStatTableRow>(FIND_ROW_CONTEXT)->BaseHealth;
			BaseHealthRegen = StatInformation.GetRow<FValorCharacterStatTableRow>(FIND_ROW_CONTEXT)->BaseHealthRegen;
			BasePrimaryResource = StatInformation.GetRow<FValorCharacterStatTableRow>(FIND_ROW_CONTEXT)->BasePrimaryResource;
			BasePrimaryResourceRegen = StatInformation.GetRow<FValorCharacterStatTableRow>(FIND_ROW_CONTEXT)->BasePrimaryResourceRegen;
			BaseSecondaryResource = StatInformation.GetRow<FValorCharacterStatTableRow>(FIND_ROW_CONTEXT)->BaseSecondaryResource;
			BaseSecondaryResourceRegen = StatInformation.GetRow<FValorCharacterStatTableRow>(FIND_ROW_CONTEXT)->BaseSecondaryResourceRegen;
			MaxSecondaryResource = StatInformation.GetRow<FValorCharacterStatTableRow>(FIND_ROW_CONTEXT)->MaxSecondaryResource;
			/* The behavior of a secondary resource will vary wildly between heros, so it is not beneficial to manipulate it here.
			* Each hero with a secondary resource should either override this method. */

			Health = GetMaxHealth();
			PrimaryResource = GetMaxPrimaryResource();
			SecondaryResource = 0;
		}

		GetWorld()->GetTimerManager().SetTimer(TimerHandle_StatRecovery, this, &AValorCharacter::RecoverStats, (GetStatRecoveryFrequencyTime() / GetStatRecoveryFrequency()), true);

		PrimaryActorTick.bCanEverTick = true;
		PrimaryActorTick.bStartWithTickEnabled = false;
	}

	if (GetNetMode() != NM_DedicatedServer)
	{
		/*
		if (RespawnParticleSystem)
		{
			UGameplayStatics::SpawnEmitterAtLocation(this, RespawnparticleSystem, GetActorLocation(), GetActorRotation());
		}
		if (RespawnSoundCue)
		{
			UGameplayStatics::PlaySoundAtLocation(this, RespawnSound, GetActorLocation());
		}
		*/
	}
}

void AValorCharacter::Tick(float DeltaSeconds)
{
	Super::Tick(DeltaSeconds);
}

void AValorCharacter::RecoverStats()
{
	Health = FMath::Clamp(Health + (GetHealthRegen() / GetStatRecoveryFrequency()), 0.f, GetMaxHealth());
	PrimaryResource = FMath::Clamp(PrimaryResource + (GetPrimaryResourceRegen() / GetStatRecoveryFrequency()), 0.f, GetMaxPrimaryResource());
	/* The behavior of a secondary resource will vary wildly between heros, so it is not beneficial to manipulate it here.
	 * Each hero with a secondary resource should either override this method or create a separate timer. */
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
		return MyPlayerState->GetTeam();
	}
	return EValorTeam::None;
}

bool AValorCharacter::IsAlive() const
{
	return Health > 0;
}

float AValorCharacter::GetMaxHealth() const
{
	const AValorPlayerState* MyPlayerState = Cast<AValorPlayerState>(PlayerState);
	if (MyPlayerState)
	{
		return BaseHealth + BonusHealthFromLevel + MyPlayerState->GetHealthFromItems();
	}
	else
	{
		return BaseHealth + BonusHealthFromLevel;
	}
}

float AValorCharacter::GetMaxPrimaryResource() const
{
	const AValorPlayerState* MyPlayerState = Cast<AValorPlayerState>(PlayerState);
	if (MyPlayerState)
	{
		return BasePrimaryResource + BonusPrimaryResourceFromLevel + MyPlayerState->GetPrimaryResourceFromItems();
	}
	else
	{
		return BasePrimaryResource + BonusPrimaryResourceFromLevel;
	}
}

float AValorCharacter::GetMaxSecondaryResource() const
{
	/* This will need some work as we make heros that utilize a secondary resource, especially
	 * if the maximum amount increases at select levels. */
	return BaseSecondaryResource;
}

float AValorCharacter::GetHealth() const
{
	return Health;
}

float AValorCharacter::GetBaseHealth() const
{
	return BaseHealth;
}

float AValorCharacter::GetHealthRegen() const
{
	const AValorPlayerState* MyPlayerState = Cast<AValorPlayerState>(PlayerState);
	if (MyPlayerState)
	{
		return BaseHealthRegen + BonusHealthRegenFromLevel + MyPlayerState->GetHealthRegenFromItems(BaseHealthRegen);
	}
	else
	{
		return BaseHealthRegen + BonusHealthRegenFromLevel;
	}
}

float AValorCharacter::GetBaseHealthRegen() const
{
	return BaseHealthRegen;
}

float AValorCharacter::GetPrimaryResource() const
{
	return PrimaryResource;
}

float AValorCharacter::GetBasePrimaryResource() const
{
	return BasePrimaryResource;
}

float AValorCharacter::GetPrimaryResourceRegen() const
{
	const AValorPlayerState* MyPlayerState = Cast<AValorPlayerState>(PlayerState);
	if (MyPlayerState)
	{
		return BasePrimaryResourceRegen + BonusPrimaryResourceRegenFromLevel + MyPlayerState->GetPrimaryResourceRegenFromItems(BasePrimaryResourceRegen);
	}
	else
	{
		return BaseHealthRegen + BonusHealthRegenFromLevel;
	}
}

float AValorCharacter::GetBasePrimaryResourceRegen() const
{
	return BasePrimaryResourceRegen;
}

float AValorCharacter::GetSecondaryResource() const
{
	return SecondaryResource;
}

float AValorCharacter::GetBaseSecondaryResource() const
{
	return BaseSecondaryResource;
}

float AValorCharacter::GetSecondaryResourceRegen() const
{
	return BaseSecondaryResource;
}

float AValorCharacter::GetBaseSecondaryResourceRegen() const
{
	return BaseSecondaryResourceRegen;
}

void AValorCharacter::OnLevelUp()
{
	const AValorPlayerState* MyPlayerState = Cast<AValorPlayerState>(PlayerState);
	if (MyPlayerState)
	{

	}
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

	DOREPLIFETIME(AValorCharacter, Health);
	DOREPLIFETIME(AValorCharacter, PrimaryResource);
	DOREPLIFETIME(AValorCharacter, SecondaryResource);
	//DOREPLIFETIME(AValorCharacter, );
	//DOREPLIFETIME(AValorCharacter, );
	//DOREPLIFETIME(AValorCharacter, );
	//DOREPLIFETIME(AValorCharacter, );
	//DOREPLIFETIME(AValorCharacter, );
	//DOREPLIFETIME(AValorCharacter, );
	//DOREPLIFETIME(AValorCharacter, Level);
	//DOREPLIFETIME(AValorCharacter, Team);
}