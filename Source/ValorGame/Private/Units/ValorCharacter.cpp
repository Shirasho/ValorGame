// Copyright Shirasho Media 2016. All rights reserved.

#include "ValorGame.h"
#include "ValorCharacter.h"

#include "ValorCollisionDefinitions.h"

#include "ValorPlayerState.h"


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

		UCharacterMovementComponent* MovementComponent = Cast<UCharacterMovementComponent>(GetMovementComponent());
		if (MovementComponent)
		{
			MovementComponent->RotationRate = FRotator(0.f, 0.f, -1.f);
			MovementComponent->bRequestedMoveUseAcceleration = false;
			MovementComponent->GroundFriction = 0.f;
		}

		CharacterTeam = EValorTeam::None;
	}

	bReplicates = true;
}


void AValorCharacter::PostInitializeComponents()
{
	Super::PostInitializeComponents();

	if (HasAuthority())
	{
		GetWorld()->GetTimerManager().SetTimer(TimerHandle_StatRecovery, this, &AValorCharacter::RecoverStats, (GetStatRecoveryFrequencyTime() / GetStatRecoveryFrequency()), true);

		PrimaryActorTick.bCanEverTick = true;
		PrimaryActorTick.bStartWithTickEnabled = false;
	}
}

void AValorCharacter::EndPlay(const EEndPlayReason::Type EndPlayReason)
{
	Super::EndPlay(EndPlayReason);

	GetWorld()->GetTimerManager().ClearTimer(TimerHandle_StatRecovery);
}

void AValorCharacter::InitStats()
{
	if (HasAuthority())
	{
		const AValorPlayerState* MyPlayerState = Cast<AValorPlayerState>(PlayerState);
		if (MyPlayerState && ensure(MyPlayerState->GetPlayerLevel() >= 1))
		{
			/* When a hero dies the character will be destroyed. That means
			* the CharacterStats will be destroyed as well. Certain stats
			* that are not grabbed from external data (like current stats)
			* will be reset to their lowest values. This is obviously not what we want.
			* These need to be grabbed from a persistent state in order to
			* properly recalculate the other stats. */

			check(MyPlayerState->GetPlayerLevel() <= VALOR_MAX_CHARACTER_LEVEL);

			/* Only perform check in development builds. */
			checkCode(if (GWorld && GWorld->HasBegunPlay())
			{
				ensureMsgf(GetCharacterStats().StatInformation.DataTable, TEXT("A ValorCharacterStatTable has not been assigned for the character '%s'."), *GetNameSafe(this));
				ensureMsgf(GetCharacterStats().ExperienceInformation.DataTable, TEXT("A ValorCharacterExperienceTable has not been assigned for the character '%s'."), *GetNameSafe(this));
			});

			if (CharacterStats.StatInformation.DataTable)
			{
				CharacterStats.StatInformation.RowName = TEXT("BaseHealth");
				switch (MyPlayerState->GetPlayerLevel())
				{
					case 1:
						CharacterStats.BaseHealth = CharacterStats.StatInformation.GetRow<FValorCharacterStatTableRow>(VALOR_DATA_ROW_CONTEXT)->L1; break;
					case 2:
						CharacterStats.BaseHealth = CharacterStats.StatInformation.GetRow<FValorCharacterStatTableRow>(VALOR_DATA_ROW_CONTEXT)->L2; break;
					case 3:
						CharacterStats.BaseHealth = CharacterStats.StatInformation.GetRow<FValorCharacterStatTableRow>(VALOR_DATA_ROW_CONTEXT)->L3; break;
					case 4:
						CharacterStats.BaseHealth = CharacterStats.StatInformation.GetRow<FValorCharacterStatTableRow>(VALOR_DATA_ROW_CONTEXT)->L4; break;
					case 5:
						CharacterStats.BaseHealth = CharacterStats.StatInformation.GetRow<FValorCharacterStatTableRow>(VALOR_DATA_ROW_CONTEXT)->L5; break;
					case 6:
						CharacterStats.BaseHealth = CharacterStats.StatInformation.GetRow<FValorCharacterStatTableRow>(VALOR_DATA_ROW_CONTEXT)->L6; break;
					case 7:
						CharacterStats.BaseHealth = CharacterStats.StatInformation.GetRow<FValorCharacterStatTableRow>(VALOR_DATA_ROW_CONTEXT)->L7; break;
					case 8:
						CharacterStats.BaseHealth = CharacterStats.StatInformation.GetRow<FValorCharacterStatTableRow>(VALOR_DATA_ROW_CONTEXT)->L8; break;
					case 9:
						CharacterStats.BaseHealth = CharacterStats.StatInformation.GetRow<FValorCharacterStatTableRow>(VALOR_DATA_ROW_CONTEXT)->L9; break;
					case 10:
						CharacterStats.BaseHealth = CharacterStats.StatInformation.GetRow<FValorCharacterStatTableRow>(VALOR_DATA_ROW_CONTEXT)->L10; break;
					case 11:
						CharacterStats.BaseHealth = CharacterStats.StatInformation.GetRow<FValorCharacterStatTableRow>(VALOR_DATA_ROW_CONTEXT)->L11; break;
					case 12:
						CharacterStats.BaseHealth = CharacterStats.StatInformation.GetRow<FValorCharacterStatTableRow>(VALOR_DATA_ROW_CONTEXT)->L12; break;
					case 13:
						CharacterStats.BaseHealth = CharacterStats.StatInformation.GetRow<FValorCharacterStatTableRow>(VALOR_DATA_ROW_CONTEXT)->L13; break;
					case 14:
						CharacterStats.BaseHealth = CharacterStats.StatInformation.GetRow<FValorCharacterStatTableRow>(VALOR_DATA_ROW_CONTEXT)->L14; break;
					case 15:
						CharacterStats.BaseHealth = CharacterStats.StatInformation.GetRow<FValorCharacterStatTableRow>(VALOR_DATA_ROW_CONTEXT)->L15; break;
					case 16:
						CharacterStats.BaseHealth = CharacterStats.StatInformation.GetRow<FValorCharacterStatTableRow>(VALOR_DATA_ROW_CONTEXT)->L16; break;
					case 17:
						CharacterStats.BaseHealth = CharacterStats.StatInformation.GetRow<FValorCharacterStatTableRow>(VALOR_DATA_ROW_CONTEXT)->L17; break;
					case 18:
						CharacterStats.BaseHealth = CharacterStats.StatInformation.GetRow<FValorCharacterStatTableRow>(VALOR_DATA_ROW_CONTEXT)->L18; break;
					case 19:
						CharacterStats.BaseHealth = CharacterStats.StatInformation.GetRow<FValorCharacterStatTableRow>(VALOR_DATA_ROW_CONTEXT)->L19; break;
					case 20:
						CharacterStats.BaseHealth = CharacterStats.StatInformation.GetRow<FValorCharacterStatTableRow>(VALOR_DATA_ROW_CONTEXT)->L20; break;
					default:
						CharacterStats.BaseHealth = 100; break;
				}
			}

			/* This system only supports item bonuses based on base and max health. More complex stuff,
			* like bonus health from regen, will need some additional tweaking. */
			if (MyPlayerState->GetPlayerLevel() > 1)
			{
				CharacterStats.BonusHealth = CharacterStats.HealthGainPerLevel[MyPlayerState->GetPlayerLevel() - 2];
			}
			CharacterStats.BonusHealth += MyPlayerState->GetPlayerHealthFromItems(CharacterStats.BaseHealth, CharacterStats.BonusHealth);
			CharacterStats.Health = CharacterStats.BaseHealth + CharacterStats.BonusHealth;

			if (MyPlayerState->GetPlayerLevel() > 1)
			{
				CharacterStats.BonusPrimaryResource = CharacterStats.PrimaryResourceGainPerLevel[MyPlayerState->GetPlayerLevel() - 2];
			}
			CharacterStats.BonusPrimaryResource += MyPlayerState->GetPlayerPrimaryResourceFromItems(CharacterStats.BasePrimaryResource, CharacterStats.BonusPrimaryResource);
			CharacterStats.PrimaryResource = CharacterStats.BasePrimaryResource + CharacterStats.BonusPrimaryResource;

			if (MyPlayerState->GetPlayerLevel() > 1)
			{
				CharacterStats.BonusSecondaryResource = CharacterStats.SecondaryResourceGainPerLevel[MyPlayerState->GetPlayerLevel() - 2];
			}
			CharacterStats.BonusSecondaryResource += MyPlayerState->GetPlayerSecondaryResourceFromItems(CharacterStats.BaseSecondaryResource, CharacterStats.BonusSecondaryResource);
			CharacterStats.SecondaryResource = CharacterStats.BaseSecondaryResource + CharacterStats.BonusSecondaryResource;


			RecalculateNonResourceStats();

		}
	}
}

void AValorCharacter::RecoverStats()
{
	RecalculateNonResourceStats();

	CharacterStats.Health = FMath::Clamp(CharacterStats.Health, CharacterStats.Health + CharacterStats.HealthRegen, CharacterStats.BaseHealth + CharacterStats.BonusHealth);
	CharacterStats.PrimaryResource = FMath::Clamp(CharacterStats.PrimaryResource, CharacterStats.PrimaryResource + CharacterStats.PrimaryResourceRegen, CharacterStats.BasePrimaryResource + CharacterStats.BonusPrimaryResource);

	/* The behavior of a secondary resource will vary wildly between heros, so it is not beneficial to manipulate it here.
	 * Each hero with a secondary resource should either override this method or create a separate timer. */
}

void AValorCharacter::RecalculateNonResourceStats()
{
	const AValorPlayerState* MyPlayerState = Cast<AValorPlayerState>(PlayerState);
	if (HasAuthority() && MyPlayerState)
	{
		if (MyPlayerState->GetPlayerLevel() > 1)
		{
			CharacterStats.BonusHealthRegen = CharacterStats.HealthRegenPerLevel[MyPlayerState->GetPlayerLevel() - 2];
		}
		CharacterStats.BonusHealthRegen += MyPlayerState->GetPlayerHealthRegenFromItems(CharacterStats.BaseHealthRegen, CharacterStats.BonusHealthRegen, CharacterStats.BaseHealth, CharacterStats.BonusHealth);
		CharacterStats.HealthRegen = CharacterStats.BaseHealthRegen + CharacterStats.BonusHealthRegen;

		if (MyPlayerState->GetPlayerLevel() > 1)
		{
			CharacterStats.BonusPrimaryResourceRegen = CharacterStats.PrimaryResourceRegenPerLevel[MyPlayerState->GetPlayerLevel() - 2];
		}
		CharacterStats.BonusPrimaryResourceRegen += MyPlayerState->GetPlayerPrimaryResourceRegenFromItems(CharacterStats.BasePrimaryResourceRegen, CharacterStats.BonusPrimaryResourceRegen, CharacterStats.BasePrimaryResource, CharacterStats.BonusPrimaryResource);
		CharacterStats.PrimaryResourceRegen = CharacterStats.BasePrimaryResourceRegen + CharacterStats.BonusPrimaryResourceRegen;

		if (MyPlayerState->GetPlayerLevel() > 1)
		{
			CharacterStats.BonusSecondaryResourceRegen = CharacterStats.SecondaryResourceRegenPerLevel[MyPlayerState->GetPlayerLevel() - 2];
		}
		CharacterStats.BonusSecondaryResourceRegen += MyPlayerState->GetPlayerSecondaryResourceRegenFromItems(CharacterStats.BaseSecondaryResourceRegen, CharacterStats.BonusSecondaryResourceRegen, CharacterStats.BaseSecondaryResource, CharacterStats.BonusSecondaryResource);
		CharacterStats.SecondaryResourceRegen = CharacterStats.BaseSecondaryResourceRegen + CharacterStats.BonusSecondaryResourceRegen;
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
	return CharacterStats.Health > 0;
}

const FValorCharacterStatContainer& AValorCharacter::GetCharacterStats() const
{
	return CharacterStats;
}

float AValorCharacter::GetMaxHealth() const
{
	return CharacterStats.Health + CharacterStats.BonusHealth;
}

float AValorCharacter::GetMaxPrimaryResource() const
{
	return CharacterStats.BasePrimaryResource + CharacterStats.BonusSecondaryResource;
}

float AValorCharacter::GetMaxSecondaryResource() const
{
	return CharacterStats.BaseSecondaryResource + CharacterStats.BonusSecondaryResource;
}

float AValorCharacter::GetHealth() const
{
	return CharacterStats.Health;
}

float AValorCharacter::GetBaseHealth() const
{
	return CharacterStats.BaseHealth;
}

float AValorCharacter::GetHealthRegen() const
{
	return CharacterStats.BaseHealthRegen + CharacterStats.BonusHealthRegen;
}

float AValorCharacter::GetBaseHealthRegen() const
{
	return CharacterStats.BaseHealthRegen;
}

float AValorCharacter::GetPrimaryResource() const
{
	return CharacterStats.PrimaryResource;
}

float AValorCharacter::GetBasePrimaryResource() const
{
	return CharacterStats.BasePrimaryResource;
}

float AValorCharacter::GetPrimaryResourceRegen() const
{
	return CharacterStats.BasePrimaryResourceRegen + CharacterStats.BonusPrimaryResourceRegen;
}

float AValorCharacter::GetBasePrimaryResourceRegen() const
{
	return CharacterStats.BasePrimaryResourceRegen;
}

float AValorCharacter::GetSecondaryResource() const
{
	return CharacterStats.SecondaryResource;
}

float AValorCharacter::GetBaseSecondaryResource() const
{
	return CharacterStats.BaseSecondaryResource;
}

float AValorCharacter::GetSecondaryResourceRegen() const
{
	return CharacterStats.BaseSecondaryResourceRegen + CharacterStats.BonusSecondaryResourceRegen;
}

float AValorCharacter::GetBaseSecondaryResourceRegen() const
{
	return CharacterStats.BaseSecondaryResourceRegen;
}

void AValorCharacter::AdjustHealth(float Value)
{
	CharacterStats.BonusHealth += Value;
}

void AValorCharacter::AdjustPrimaryResource(float Value)
{
	CharacterStats.BonusPrimaryResource += Value;
}

void AValorCharacter::AdjustSecondaryResource(float Value)
{
	CharacterStats.BonusSecondaryResource += Value;
}

void AValorCharacter::AdjustHealthRegen(float Value)
{
	CharacterStats.BonusHealthRegen += Value;
}

void AValorCharacter::AdjustPrimaryResourceRegen(float Value)
{
	CharacterStats.BonusPrimaryResourceRegen += Value;
}

void AValorCharacter::AdjustSecondaryResourceRegen(float Value)
{
	CharacterStats.BonusSecondaryResourceRegen += Value;
}

void AValorCharacter::IncrementLevel()
{
	AValorPlayerState* MyPlayerState = Cast<AValorPlayerState>(PlayerState);
	if (MyPlayerState)
	{
		MyPlayerState->IncrementPlayerLevel(CharacterStats.ExperienceRequiredPerLevel);
	}
}

void AValorCharacter::OnLevelUp()
{
	
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

	//DOREPLIFETIME(AValorCharacter, Health);
	//DOREPLIFETIME(AValorCharacter, PrimaryResource);
	//DOREPLIFETIME(AValorCharacter, SecondaryResource);
	DOREPLIFETIME(AValorCharacter, CharacterStats);
	DOREPLIFETIME(AValorCharacter, CharacterTeam); // Mostly here for minions - player's team will properly replicate through PlayerState.
	//DOREPLIFETIME(AValorCharacter, );
	//DOREPLIFETIME(AValorCharacter, );
	//DOREPLIFETIME(AValorCharacter, );
	//DOREPLIFETIME(AValorCharacter, );
	//DOREPLIFETIME(AValorCharacter, Level);
	//DOREPLIFETIME(AValorCharacter, Team);
}