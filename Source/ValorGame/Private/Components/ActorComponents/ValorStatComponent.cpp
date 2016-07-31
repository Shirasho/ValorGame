// Copyright Shirasho Media 2016. All rights reserved.

#include "ValorGame.h"
#include "ValorStatComponent.h"

#include "ValorCharacter.h"
#include "ValorPlayerState.h"

#define VALOR_MAX_CHARACTER_LEVEL 20

#define ADD_STAT(ArrayName, StatName, Container, TableRowType, UnitLevel) Container.RowName = TEXT( #StatName ); ArrayName.Add( Container.GetRow< TableRowType >(VALOR_DATA_ROW_CONTEXT)->L##UnitLevel )
																		
// Sets default values for this component's properties
UValorStatComponent::UValorStatComponent()
{
	bRequiresStatInformation = true;
	bWantsBeginPlay = true;
	bSetupComplete = false;
	PrimaryComponentTick.bCanEverTick = true;
	PrimaryComponentTick.bStartWithTickEnabled = false;
}

void UValorStatComponent::BeginPlay()
{
	Super::BeginPlay();
	Health = 100;
	PrimaryResource = 0;
	SecondaryResource = 0;
	HealthRegen = 0;
	PrimaryResourceRegen = 0;
	SecondaryResourceRegen = 0;

	if (bRequiresStatInformation)
	{
		if (!StatInformation.DataTable)
		{
			UE_LOG(LogValorCharacter, Log, TEXT("Stat information is null for character '%s'. Assign one in the editor."), *GetNameSafe(GetOwner()));
		}
		else
		{
			ensure(StatInformation.DataTable->RowStruct->IsChildOf(FValorCharacterStatTableRow::StaticStruct()));
		}

		if (!ExperienceInformation.DataTable)
		{
			UE_LOG(LogValorCharacter, Log, TEXT("Experience information is null for character '%s'. Assign one in the editor."), *GetNameSafe(GetOwner()));
		}
		else
		{
			ensure(ExperienceInformation.DataTable->RowStruct->IsChildOf(FValorCharacterExperienceTableRow::StaticStruct()));
			ExperienceInformation.RowName = TEXT("Value");
		}
	}

	GetWorld()->GetTimerManager().SetTimer(TimerHandle_RecoverStats, this, &UValorStatComponent::RecoverStats, GetWorld()->GetWorldSettings()->GetEffectiveTimeDilation() * (5.f / RecoverTickFrequency), true);
}

void UValorStatComponent::TickComponent( float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction )
{
	Super::TickComponent( DeltaTime, TickType, ThisTickFunction );
}


void UValorStatComponent::RecoverStats()
{
	if (bSetupComplete)
	{
		Health = FMath::Clamp(Health + GetHealthRegen(), 0.f, GetMaxHealth());
		PrimaryResource = FMath::Clamp(PrimaryResource + GetPrimaryResourceRegen(), 0.f, GetMaxPrimaryResource());
		SecondaryResource = FMath::Clamp(SecondaryResource + GetSecondaryResourceRegen(), 0.f, GetMaxSecondaryResource());
	}
}

void UValorStatComponent::RecalculateStats(const bool bOnInit, const bool bOnLevelUp)
{
	const AValorCharacter* Owner = Cast<AValorCharacter>(GetOwner());
	AValorPlayerState* OuterPlayerState = nullptr;

	if (bRequiresStatInformation && StatInformation.DataTable)
	{
		if (Owner)
		{
			AValorPlayerState* PlayerState = Cast<AValorPlayerState>(Owner->PlayerState);
			if (PlayerState && ensure(PlayerState->GetPlayerLevel() >= 1) && ensure(PlayerState->GetPlayerLevel() <= VALOR_MAX_CHARACTER_LEVEL))
			{
				OuterPlayerState = PlayerState;
				Level = PlayerState->GetPlayerLevel();
			}
			else
			{
				Level = 1;
			}

			if (!bOnLevelUp && bOnInit)
			{
				SetBaseStats();
			}

			SetBonusHealth(PlayerState);
			SetBonusPrimaryResource(PlayerState);
			SetBonusSecondaryResource(PlayerState);
			SetBonusHealthRegen(PlayerState);
			SetBonusPrimaryResourceRegen(PlayerState);
			SetBonusSecondaryResourceRegen(PlayerState);
		}

		HealthRegen = GetBaseHealthRegen() + GetBonusHealthRegen();
		PrimaryResourceRegen = GetBasePrimaryResourceRegen() + GetBonusPrimaryResourceRegen();
		SecondaryResourceRegen = GetBaseSecondaryResourceRegen() + GetBonusSecondaryResourceRegen();
	}
	if (ExperienceInformation.DataTable)
	{
		const AValorPlayerState* PlayerState = Cast<AValorPlayerState>(Owner->PlayerState);
		if (PlayerState && ensure(PlayerState->GetPlayerExperience() >= 0))
		{
			Experience = PlayerState->GetPlayerExperience();
			if (!bOnLevelUp && bOnInit)
			{
				SetBaseExperience();
			}
		}
	}

	SetHealth(OuterPlayerState, bOnInit, bOnLevelUp);
	SetPrimaryResource(OuterPlayerState, bOnInit, bOnLevelUp);
	SetSecondaryResource(OuterPlayerState, bOnInit, bOnLevelUp);

	bSetupComplete = true;
}

float UValorStatComponent::GetHealth() const
{
	return Health;
}

float UValorStatComponent::GetPrimaryResource() const
{
	return PrimaryResource;
}

float UValorStatComponent::GetSecondaryResource() const
{
	return SecondaryResource;
}

float UValorStatComponent::GetMaxHealth() const
{
	return GetBaseHealth() + GetBonusHealth();
}

float UValorStatComponent::GetMaxPrimaryResource() const
{
	return GetBasePrimaryResource() + GetBonusPrimaryResource();
}

float UValorStatComponent::GetMaxSecondaryResource() const
{
	return GetBaseSecondaryResource() + GetBonusSecondaryResource();
}

float UValorStatComponent::GetBaseHealth() const
{
	return bRequiresStatInformation ? BaseHealthPerLevel[Level] : 100.f;
}

float UValorStatComponent::GetBonusHealth() const
{
	return BonusHealth;
}

float UValorStatComponent::GetHealthRegen() const
{
	return HealthRegen;
}

float UValorStatComponent::GetBaseHealthRegen() const
{
	return bRequiresStatInformation ? BaseHealthRegenPerLevel[Level-1] : 100.f;
}

float UValorStatComponent::GetBonusHealthRegen() const
{
	return BonusHealthRegen;
}

float UValorStatComponent::GetBonusPrimaryResource() const
{
	return BonusPrimaryResource;
}

float UValorStatComponent::GetBonusSecondaryResource() const
{
	return BonusSecondaryResource;
}

float UValorStatComponent::GetBasePrimaryResource() const
{
	return bRequiresStatInformation ? BasePrimaryResourcePerLevel[Level-1] : 0.f;
}

float UValorStatComponent::GetPrimaryResourceRegen() const
{
	return PrimaryResourceRegen;
}

float UValorStatComponent::GetBasePrimaryResourceRegen() const
{
	return bRequiresStatInformation ? BasePrimaryResourceRegenPerLevel[Level-1] : 0.f;
}

float UValorStatComponent::GetBaseSecondaryResourceRegen() const
{
	return bRequiresStatInformation ? BaseSecondaryResourceRegenPerLevel[Level-1] : 0.f;
}

float UValorStatComponent::GetBonusPrimaryResourceRegen() const
{
	return BonusPrimaryResourceRegen;
}

float UValorStatComponent::GetBonusSecondaryResourceRegen() const
{
	return BonusSecondaryResourceRegen;
}

float UValorStatComponent::GetBaseSecondaryResource() const
{
	return bRequiresStatInformation ? BaseSecondaryResourcePerLevel[Level-1] : 0.f;
}

float UValorStatComponent::GetSecondaryResourceRegen() const
{
	return SecondaryResourceRegen;
}


void UValorStatComponent::AdjustHealth(float Value)
{
	Health = FMath::Clamp(Health + Value, 0.f, GetMaxHealth());
}

void UValorStatComponent::AdjustPrimaryResource(float Value)
{
	PrimaryResource = FMath::Clamp(PrimaryResource + Value, 0.f, GetMaxPrimaryResource());
}

void UValorStatComponent::AdjustSecondaryResource(float Value)
{
	SecondaryResource = FMath::Clamp(SecondaryResource + Value, 0.f, GetMaxSecondaryResource());
}

void UValorStatComponent::AdjustHealthRegen(float Value)
{
	HealthRegen = FMath::Max(HealthRegen + Value, 0.f);
}

void UValorStatComponent::AdjustPrimaryResourceRegen(float Value)
{
	PrimaryResourceRegen = FMath::Max(PrimaryResourceRegen + Value, 0.f);
}

void UValorStatComponent::AdjustSecondaryResourceRegen(float Value)
{
	SecondaryResourceRegen = FMath::Max(SecondaryResourceRegen + Value, 0.f);
}

PRAGMA_DISABLE_OPTIMIZATION
void UValorStatComponent::SetBaseStats()
{
#pragma region BaseHealthPerLevel
	BaseHealthPerLevel.Reserve(VALOR_MAX_CHARACTER_LEVEL);
	ADD_STAT(BaseHealthPerLevel, BaseHealth, StatInformation, FValorCharacterStatTableRow, 1);
	ADD_STAT(BaseHealthPerLevel, BaseHealth, StatInformation, FValorCharacterStatTableRow, 2);
	ADD_STAT(BaseHealthPerLevel, BaseHealth, StatInformation, FValorCharacterStatTableRow, 3);
	ADD_STAT(BaseHealthPerLevel, BaseHealth, StatInformation, FValorCharacterStatTableRow, 4);
	ADD_STAT(BaseHealthPerLevel, BaseHealth, StatInformation, FValorCharacterStatTableRow, 5);
	ADD_STAT(BaseHealthPerLevel, BaseHealth, StatInformation, FValorCharacterStatTableRow, 6);
	ADD_STAT(BaseHealthPerLevel, BaseHealth, StatInformation, FValorCharacterStatTableRow, 7);
	ADD_STAT(BaseHealthPerLevel, BaseHealth, StatInformation, FValorCharacterStatTableRow, 8);
	ADD_STAT(BaseHealthPerLevel, BaseHealth, StatInformation, FValorCharacterStatTableRow, 9);
	ADD_STAT(BaseHealthPerLevel, BaseHealth, StatInformation, FValorCharacterStatTableRow, 10);
	ADD_STAT(BaseHealthPerLevel, BaseHealth, StatInformation, FValorCharacterStatTableRow, 11);
	ADD_STAT(BaseHealthPerLevel, BaseHealth, StatInformation, FValorCharacterStatTableRow, 12);
	ADD_STAT(BaseHealthPerLevel, BaseHealth, StatInformation, FValorCharacterStatTableRow, 13);
	ADD_STAT(BaseHealthPerLevel, BaseHealth, StatInformation, FValorCharacterStatTableRow, 14);
	ADD_STAT(BaseHealthPerLevel, BaseHealth, StatInformation, FValorCharacterStatTableRow, 15);
	ADD_STAT(BaseHealthPerLevel, BaseHealth, StatInformation, FValorCharacterStatTableRow, 16);
	ADD_STAT(BaseHealthPerLevel, BaseHealth, StatInformation, FValorCharacterStatTableRow, 17);
	ADD_STAT(BaseHealthPerLevel, BaseHealth, StatInformation, FValorCharacterStatTableRow, 18);
	ADD_STAT(BaseHealthPerLevel, BaseHealth, StatInformation, FValorCharacterStatTableRow, 19);
	ADD_STAT(BaseHealthPerLevel, BaseHealth, StatInformation, FValorCharacterStatTableRow, 20);
#pragma endregion

#pragma region BasePrimaryResourcePerLevel
	BasePrimaryResourcePerLevel.Reserve(VALOR_MAX_CHARACTER_LEVEL);
	ADD_STAT(BasePrimaryResourcePerLevel, BasePrimaryResource, StatInformation, FValorCharacterStatTableRow, 1);
	ADD_STAT(BasePrimaryResourcePerLevel, BasePrimaryResource, StatInformation, FValorCharacterStatTableRow, 2);
	ADD_STAT(BasePrimaryResourcePerLevel, BasePrimaryResource, StatInformation, FValorCharacterStatTableRow, 3);
	ADD_STAT(BasePrimaryResourcePerLevel, BasePrimaryResource, StatInformation, FValorCharacterStatTableRow, 4);
	ADD_STAT(BasePrimaryResourcePerLevel, BasePrimaryResource, StatInformation, FValorCharacterStatTableRow, 5);
	ADD_STAT(BasePrimaryResourcePerLevel, BasePrimaryResource, StatInformation, FValorCharacterStatTableRow, 6);
	ADD_STAT(BasePrimaryResourcePerLevel, BasePrimaryResource, StatInformation, FValorCharacterStatTableRow, 7);
	ADD_STAT(BasePrimaryResourcePerLevel, BasePrimaryResource, StatInformation, FValorCharacterStatTableRow, 8);
	ADD_STAT(BasePrimaryResourcePerLevel, BasePrimaryResource, StatInformation, FValorCharacterStatTableRow, 9);
	ADD_STAT(BasePrimaryResourcePerLevel, BasePrimaryResource, StatInformation, FValorCharacterStatTableRow, 10);
	ADD_STAT(BasePrimaryResourcePerLevel, BasePrimaryResource, StatInformation, FValorCharacterStatTableRow, 11);
	ADD_STAT(BasePrimaryResourcePerLevel, BasePrimaryResource, StatInformation, FValorCharacterStatTableRow, 12);
	ADD_STAT(BasePrimaryResourcePerLevel, BasePrimaryResource, StatInformation, FValorCharacterStatTableRow, 13);
	ADD_STAT(BasePrimaryResourcePerLevel, BasePrimaryResource, StatInformation, FValorCharacterStatTableRow, 14);
	ADD_STAT(BasePrimaryResourcePerLevel, BasePrimaryResource, StatInformation, FValorCharacterStatTableRow, 15);
	ADD_STAT(BasePrimaryResourcePerLevel, BasePrimaryResource, StatInformation, FValorCharacterStatTableRow, 16);
	ADD_STAT(BasePrimaryResourcePerLevel, BasePrimaryResource, StatInformation, FValorCharacterStatTableRow, 17);
	ADD_STAT(BasePrimaryResourcePerLevel, BasePrimaryResource, StatInformation, FValorCharacterStatTableRow, 18);
	ADD_STAT(BasePrimaryResourcePerLevel, BasePrimaryResource, StatInformation, FValorCharacterStatTableRow, 19);
	ADD_STAT(BasePrimaryResourcePerLevel, BasePrimaryResource, StatInformation, FValorCharacterStatTableRow, 20);
#pragma endregion

#pragma region BaseSecondaryResourcePerLevel
	BaseSecondaryResourcePerLevel.Reserve(VALOR_MAX_CHARACTER_LEVEL);
	ADD_STAT(BaseSecondaryResourcePerLevel, BaseSecondaryResource, StatInformation, FValorCharacterStatTableRow, 1);
	ADD_STAT(BaseSecondaryResourcePerLevel, BaseSecondaryResource, StatInformation, FValorCharacterStatTableRow, 2);
	ADD_STAT(BaseSecondaryResourcePerLevel, BaseSecondaryResource, StatInformation, FValorCharacterStatTableRow, 3);
	ADD_STAT(BaseSecondaryResourcePerLevel, BaseSecondaryResource, StatInformation, FValorCharacterStatTableRow, 4);
	ADD_STAT(BaseSecondaryResourcePerLevel, BaseSecondaryResource, StatInformation, FValorCharacterStatTableRow, 5);
	ADD_STAT(BaseSecondaryResourcePerLevel, BaseSecondaryResource, StatInformation, FValorCharacterStatTableRow, 6);
	ADD_STAT(BaseSecondaryResourcePerLevel, BaseSecondaryResource, StatInformation, FValorCharacterStatTableRow, 7);
	ADD_STAT(BaseSecondaryResourcePerLevel, BaseSecondaryResource, StatInformation, FValorCharacterStatTableRow, 8);
	ADD_STAT(BaseSecondaryResourcePerLevel, BaseSecondaryResource, StatInformation, FValorCharacterStatTableRow, 9);
	ADD_STAT(BaseSecondaryResourcePerLevel, BaseSecondaryResource, StatInformation, FValorCharacterStatTableRow, 10);
	ADD_STAT(BaseSecondaryResourcePerLevel, BaseSecondaryResource, StatInformation, FValorCharacterStatTableRow, 11);
	ADD_STAT(BaseSecondaryResourcePerLevel, BaseSecondaryResource, StatInformation, FValorCharacterStatTableRow, 12);
	ADD_STAT(BaseSecondaryResourcePerLevel, BaseSecondaryResource, StatInformation, FValorCharacterStatTableRow, 13);
	ADD_STAT(BaseSecondaryResourcePerLevel, BaseSecondaryResource, StatInformation, FValorCharacterStatTableRow, 14);
	ADD_STAT(BaseSecondaryResourcePerLevel, BaseSecondaryResource, StatInformation, FValorCharacterStatTableRow, 15);
	ADD_STAT(BaseSecondaryResourcePerLevel, BaseSecondaryResource, StatInformation, FValorCharacterStatTableRow, 16);
	ADD_STAT(BaseSecondaryResourcePerLevel, BaseSecondaryResource, StatInformation, FValorCharacterStatTableRow, 17);
	ADD_STAT(BaseSecondaryResourcePerLevel, BaseSecondaryResource, StatInformation, FValorCharacterStatTableRow, 18);
	ADD_STAT(BaseSecondaryResourcePerLevel, BaseSecondaryResource, StatInformation, FValorCharacterStatTableRow, 19);
	ADD_STAT(BaseSecondaryResourcePerLevel, BaseSecondaryResource, StatInformation, FValorCharacterStatTableRow, 20);
#pragma endregion

#pragma region BaseHealthRegenPerLevel
	BaseHealthRegenPerLevel.Reserve(VALOR_MAX_CHARACTER_LEVEL);
	ADD_STAT(BaseHealthRegenPerLevel, BaseHealthRegen, StatInformation, FValorCharacterStatTableRow, 1);
	ADD_STAT(BaseHealthRegenPerLevel, BaseHealthRegen, StatInformation, FValorCharacterStatTableRow, 2);
	ADD_STAT(BaseHealthRegenPerLevel, BaseHealthRegen, StatInformation, FValorCharacterStatTableRow, 3);
	ADD_STAT(BaseHealthRegenPerLevel, BaseHealthRegen, StatInformation, FValorCharacterStatTableRow, 4);
	ADD_STAT(BaseHealthRegenPerLevel, BaseHealthRegen, StatInformation, FValorCharacterStatTableRow, 5);
	ADD_STAT(BaseHealthRegenPerLevel, BaseHealthRegen, StatInformation, FValorCharacterStatTableRow, 6);
	ADD_STAT(BaseHealthRegenPerLevel, BaseHealthRegen, StatInformation, FValorCharacterStatTableRow, 7);
	ADD_STAT(BaseHealthRegenPerLevel, BaseHealthRegen, StatInformation, FValorCharacterStatTableRow, 8);
	ADD_STAT(BaseHealthRegenPerLevel, BaseHealthRegen, StatInformation, FValorCharacterStatTableRow, 9);
	ADD_STAT(BaseHealthRegenPerLevel, BaseHealthRegen, StatInformation, FValorCharacterStatTableRow, 10);
	ADD_STAT(BaseHealthRegenPerLevel, BaseHealthRegen, StatInformation, FValorCharacterStatTableRow, 11);
	ADD_STAT(BaseHealthRegenPerLevel, BaseHealthRegen, StatInformation, FValorCharacterStatTableRow, 12);
	ADD_STAT(BaseHealthRegenPerLevel, BaseHealthRegen, StatInformation, FValorCharacterStatTableRow, 13);
	ADD_STAT(BaseHealthRegenPerLevel, BaseHealthRegen, StatInformation, FValorCharacterStatTableRow, 14);
	ADD_STAT(BaseHealthRegenPerLevel, BaseHealthRegen, StatInformation, FValorCharacterStatTableRow, 15);
	ADD_STAT(BaseHealthRegenPerLevel, BaseHealthRegen, StatInformation, FValorCharacterStatTableRow, 16);
	ADD_STAT(BaseHealthRegenPerLevel, BaseHealthRegen, StatInformation, FValorCharacterStatTableRow, 17);
	ADD_STAT(BaseHealthRegenPerLevel, BaseHealthRegen, StatInformation, FValorCharacterStatTableRow, 18);
	ADD_STAT(BaseHealthRegenPerLevel, BaseHealthRegen, StatInformation, FValorCharacterStatTableRow, 19);
	ADD_STAT(BaseHealthRegenPerLevel, BaseHealthRegen, StatInformation, FValorCharacterStatTableRow, 20);
#pragma endregion

#pragma region BasePrimaryResourceRegenPerLevel
	BasePrimaryResourceRegenPerLevel.Reserve(VALOR_MAX_CHARACTER_LEVEL);
	ADD_STAT(BasePrimaryResourceRegenPerLevel, BasePrimaryResourceRegen, StatInformation, FValorCharacterStatTableRow, 1);
	ADD_STAT(BasePrimaryResourceRegenPerLevel, BasePrimaryResourceRegen, StatInformation, FValorCharacterStatTableRow, 2);
	ADD_STAT(BasePrimaryResourceRegenPerLevel, BasePrimaryResourceRegen, StatInformation, FValorCharacterStatTableRow, 3);
	ADD_STAT(BasePrimaryResourceRegenPerLevel, BasePrimaryResourceRegen, StatInformation, FValorCharacterStatTableRow, 4);
	ADD_STAT(BasePrimaryResourceRegenPerLevel, BasePrimaryResourceRegen, StatInformation, FValorCharacterStatTableRow, 5);
	ADD_STAT(BasePrimaryResourceRegenPerLevel, BasePrimaryResourceRegen, StatInformation, FValorCharacterStatTableRow, 6);
	ADD_STAT(BasePrimaryResourceRegenPerLevel, BasePrimaryResourceRegen, StatInformation, FValorCharacterStatTableRow, 7);
	ADD_STAT(BasePrimaryResourceRegenPerLevel, BasePrimaryResourceRegen, StatInformation, FValorCharacterStatTableRow, 8);
	ADD_STAT(BasePrimaryResourceRegenPerLevel, BasePrimaryResourceRegen, StatInformation, FValorCharacterStatTableRow, 9);
	ADD_STAT(BasePrimaryResourceRegenPerLevel, BasePrimaryResourceRegen, StatInformation, FValorCharacterStatTableRow, 10);
	ADD_STAT(BasePrimaryResourceRegenPerLevel, BasePrimaryResourceRegen, StatInformation, FValorCharacterStatTableRow, 11);
	ADD_STAT(BasePrimaryResourceRegenPerLevel, BasePrimaryResourceRegen, StatInformation, FValorCharacterStatTableRow, 12);
	ADD_STAT(BasePrimaryResourceRegenPerLevel, BasePrimaryResourceRegen, StatInformation, FValorCharacterStatTableRow, 13);
	ADD_STAT(BasePrimaryResourceRegenPerLevel, BasePrimaryResourceRegen, StatInformation, FValorCharacterStatTableRow, 14);
	ADD_STAT(BasePrimaryResourceRegenPerLevel, BasePrimaryResourceRegen, StatInformation, FValorCharacterStatTableRow, 15);
	ADD_STAT(BasePrimaryResourceRegenPerLevel, BasePrimaryResourceRegen, StatInformation, FValorCharacterStatTableRow, 16);
	ADD_STAT(BasePrimaryResourceRegenPerLevel, BasePrimaryResourceRegen, StatInformation, FValorCharacterStatTableRow, 17);
	ADD_STAT(BasePrimaryResourceRegenPerLevel, BasePrimaryResourceRegen, StatInformation, FValorCharacterStatTableRow, 18);
	ADD_STAT(BasePrimaryResourceRegenPerLevel, BasePrimaryResourceRegen, StatInformation, FValorCharacterStatTableRow, 19);
	ADD_STAT(BasePrimaryResourceRegenPerLevel, BasePrimaryResourceRegen, StatInformation, FValorCharacterStatTableRow, 20);
#pragma endregion

#pragma region BaseSecondaryResourceRegenPerLevel
	BaseSecondaryResourceRegenPerLevel.Reserve(VALOR_MAX_CHARACTER_LEVEL);
	ADD_STAT(BaseSecondaryResourceRegenPerLevel, BaseSecondaryResourceRegen, StatInformation, FValorCharacterStatTableRow, 1);
	ADD_STAT(BaseSecondaryResourceRegenPerLevel, BaseSecondaryResourceRegen, StatInformation, FValorCharacterStatTableRow, 2);
	ADD_STAT(BaseSecondaryResourceRegenPerLevel, BaseSecondaryResourceRegen, StatInformation, FValorCharacterStatTableRow, 3);
	ADD_STAT(BaseSecondaryResourceRegenPerLevel, BaseSecondaryResourceRegen, StatInformation, FValorCharacterStatTableRow, 4);
	ADD_STAT(BaseSecondaryResourceRegenPerLevel, BaseSecondaryResourceRegen, StatInformation, FValorCharacterStatTableRow, 5);
	ADD_STAT(BaseSecondaryResourceRegenPerLevel, BaseSecondaryResourceRegen, StatInformation, FValorCharacterStatTableRow, 6);
	ADD_STAT(BaseSecondaryResourceRegenPerLevel, BaseSecondaryResourceRegen, StatInformation, FValorCharacterStatTableRow, 7);
	ADD_STAT(BaseSecondaryResourceRegenPerLevel, BaseSecondaryResourceRegen, StatInformation, FValorCharacterStatTableRow, 8);
	ADD_STAT(BaseSecondaryResourceRegenPerLevel, BaseSecondaryResourceRegen, StatInformation, FValorCharacterStatTableRow, 9);
	ADD_STAT(BaseSecondaryResourceRegenPerLevel, BaseSecondaryResourceRegen, StatInformation, FValorCharacterStatTableRow, 10);
	ADD_STAT(BaseSecondaryResourceRegenPerLevel, BaseSecondaryResourceRegen, StatInformation, FValorCharacterStatTableRow, 11);
	ADD_STAT(BaseSecondaryResourceRegenPerLevel, BaseSecondaryResourceRegen, StatInformation, FValorCharacterStatTableRow, 12);
	ADD_STAT(BaseSecondaryResourceRegenPerLevel, BaseSecondaryResourceRegen, StatInformation, FValorCharacterStatTableRow, 13);
	ADD_STAT(BaseSecondaryResourceRegenPerLevel, BaseSecondaryResourceRegen, StatInformation, FValorCharacterStatTableRow, 14);
	ADD_STAT(BaseSecondaryResourceRegenPerLevel, BaseSecondaryResourceRegen, StatInformation, FValorCharacterStatTableRow, 15);
	ADD_STAT(BaseSecondaryResourceRegenPerLevel, BaseSecondaryResourceRegen, StatInformation, FValorCharacterStatTableRow, 16);
	ADD_STAT(BaseSecondaryResourceRegenPerLevel, BaseSecondaryResourceRegen, StatInformation, FValorCharacterStatTableRow, 17);
	ADD_STAT(BaseSecondaryResourceRegenPerLevel, BaseSecondaryResourceRegen, StatInformation, FValorCharacterStatTableRow, 18);
	ADD_STAT(BaseSecondaryResourceRegenPerLevel, BaseSecondaryResourceRegen, StatInformation, FValorCharacterStatTableRow, 19);
	ADD_STAT(BaseSecondaryResourceRegenPerLevel, BaseSecondaryResourceRegen, StatInformation, FValorCharacterStatTableRow, 20);
#pragma endregion
}
PRAGMA_ENABLE_OPTIMIZATION

void UValorStatComponent::SetBaseExperience()
{
	ADD_STAT(ExperienceRequiredPerLevel, Value, ExperienceInformation, FValorCharacterExperienceTableRow, 2);
	ADD_STAT(ExperienceRequiredPerLevel, Value, ExperienceInformation, FValorCharacterExperienceTableRow, 3);
	ADD_STAT(ExperienceRequiredPerLevel, Value, ExperienceInformation, FValorCharacterExperienceTableRow, 4);
	ADD_STAT(ExperienceRequiredPerLevel, Value, ExperienceInformation, FValorCharacterExperienceTableRow, 5);
	ADD_STAT(ExperienceRequiredPerLevel, Value, ExperienceInformation, FValorCharacterExperienceTableRow, 6);
	ADD_STAT(ExperienceRequiredPerLevel, Value, ExperienceInformation, FValorCharacterExperienceTableRow, 7);
	ADD_STAT(ExperienceRequiredPerLevel, Value, ExperienceInformation, FValorCharacterExperienceTableRow, 8);
	ADD_STAT(ExperienceRequiredPerLevel, Value, ExperienceInformation, FValorCharacterExperienceTableRow, 9);
	ADD_STAT(ExperienceRequiredPerLevel, Value, ExperienceInformation, FValorCharacterExperienceTableRow, 10);
	ADD_STAT(ExperienceRequiredPerLevel, Value, ExperienceInformation, FValorCharacterExperienceTableRow, 11);
	ADD_STAT(ExperienceRequiredPerLevel, Value, ExperienceInformation, FValorCharacterExperienceTableRow, 12);
	ADD_STAT(ExperienceRequiredPerLevel, Value, ExperienceInformation, FValorCharacterExperienceTableRow, 13);
	ADD_STAT(ExperienceRequiredPerLevel, Value, ExperienceInformation, FValorCharacterExperienceTableRow, 14);
	ADD_STAT(ExperienceRequiredPerLevel, Value, ExperienceInformation, FValorCharacterExperienceTableRow, 15);
	ADD_STAT(ExperienceRequiredPerLevel, Value, ExperienceInformation, FValorCharacterExperienceTableRow, 16);
	ADD_STAT(ExperienceRequiredPerLevel, Value, ExperienceInformation, FValorCharacterExperienceTableRow, 17);
	ADD_STAT(ExperienceRequiredPerLevel, Value, ExperienceInformation, FValorCharacterExperienceTableRow, 18);
	ADD_STAT(ExperienceRequiredPerLevel, Value, ExperienceInformation, FValorCharacterExperienceTableRow, 19);
	ADD_STAT(ExperienceRequiredPerLevel, Value, ExperienceInformation, FValorCharacterExperienceTableRow, 20);
}

void UValorStatComponent::SetBonusHealth(const AValorPlayerState* PlayerState)
{
	if (PlayerState)
	{
		BonusHealth = PlayerState->GetPlayerHealthFromItems(GetBaseHealth(), 0.f); //Excludes modifiers from passive and abilities.
	}
	else
	{
		BonusHealth = 0;
	}
}
void UValorStatComponent::SetBonusPrimaryResource(const AValorPlayerState* PlayerState)
{
	if (PlayerState)
	{
		BonusPrimaryResource = PlayerState->GetPlayerPrimaryResourceFromItems(GetBasePrimaryResource(), 0.f); //Excludes modifiers from passive and abilities.
	}
	else
	{
		BonusPrimaryResource = 0;
	}
}
void UValorStatComponent::SetBonusSecondaryResource(const AValorPlayerState* PlayerState)
{
	if (PlayerState)
	{
		BonusSecondaryResource = PlayerState->GetPlayerSecondaryResourceFromItems(GetBaseSecondaryResource(), 0.f); //Excludes modifiers from passive and abilities.
	}
	else
	{
		BonusSecondaryResource = 0;
	}
}
void UValorStatComponent::SetBonusHealthRegen(const AValorPlayerState* PlayerState)
{
	if (PlayerState)
	{
		BonusHealthRegen = PlayerState->GetPlayerHealthRegenFromItems(GetBaseHealthRegen(), 0.f, GetBaseHealth(), GetBonusHealth()); //Excludes modifiers from passive and abilities.
	}
	else
	{
		BonusHealthRegen = 0;
	}
}
void UValorStatComponent::SetBonusPrimaryResourceRegen(const AValorPlayerState* PlayerState)
{
	if (PlayerState)
	{
		BonusPrimaryResourceRegen = PlayerState->GetPlayerPrimaryResourceRegenFromItems(GetBasePrimaryResourceRegen(), 0.f, GetBasePrimaryResource(), GetBonusPrimaryResource()); //Excludes modifiers from passive and abilities.
	}
	else
	{
		BonusPrimaryResourceRegen = 0;
	}
}
void UValorStatComponent::SetBonusSecondaryResourceRegen(const AValorPlayerState* PlayerState)
{
	if (PlayerState)
	{
		BonusSecondaryResourceRegen = PlayerState->GetPlayerSecondaryResourceRegenFromItems(GetBaseSecondaryResourceRegen(), 0.f, GetBaseSecondaryResource(), GetBonusSecondaryResource()); //Excludes modifiers from passive and abilities.
	}
	else
	{
		BonusSecondaryResourceRegen = 0;
	}
}

void UValorStatComponent::SetHealth(const AValorPlayerState* PlayerState, const bool bOnInit, const bool bOnLevelUp)
{
	if (!bOnLevelUp && bOnInit && PlayerState)
	{
		Health = GetMaxHealth();
	}
	else if (!bOnInit && bOnLevelUp && PlayerState)
	{
		check(Level >= 2);
		Health = FMath::Clamp(Health + BaseHealthPerLevel[Level - 1] - BaseHealthPerLevel[Level - 2], 0.f, GetMaxHealth());
	}
	else if (!bOnInit && !bOnLevelUp && PlayerState)
	{
		// This case would be hit whenever an item is bought in the store.
		// We could theoretically up the player's health by the new item's
		// bonus here, but for now new purchases do not increase the stat's
		// current value, only the maximum.
	}
	else
	{
		//@TODO Handle minion regen here.
	}
}
void UValorStatComponent::SetPrimaryResource(const AValorPlayerState* PlayerState, const bool bOnInit, const bool bOnLevelUp)
{
	if (!bOnLevelUp && PlayerState)
	{
		PrimaryResource = GetMaxPrimaryResource();
	}
	else if (bOnLevelUp && PlayerState)
	{
		check(Level >= 2);
		PrimaryResource = FMath::Clamp(PrimaryResource + BasePrimaryResourcePerLevel[Level - 1] - BasePrimaryResourcePerLevel[Level - 2], 0.f, GetMaxPrimaryResource());
	}
	else if (!bOnInit && !bOnLevelUp && PlayerState)
	{
		// This case would be hit whenever an item is bought in the store.
		// We could theoretically up the player's primary resource by the new item's
		// bonus here, but for now new purchases do not increase the stat's
		// current value, only the maximum.
	}
	else
	{
		//@TODO Handle minion regen here.
	}
}
void UValorStatComponent::SetSecondaryResource(const AValorPlayerState* PlayerState, const bool bOnInit, const bool bOnLevelUp)
{
	if (!bOnLevelUp && PlayerState)
	{
		SecondaryResource = GetMaxSecondaryResource();
	}
	else if (bOnLevelUp && PlayerState)
	{
		check(Level >= 2);
		SecondaryResource = FMath::Clamp(SecondaryResource + BaseSecondaryResourcePerLevel[Level - 1] - BaseSecondaryResourcePerLevel[Level - 2], 0.f, GetMaxSecondaryResource());
	}
	else if (!bOnInit && !bOnLevelUp && PlayerState)
	{
		// This case would be hit whenever an item is bought in the store.
		// We could theoretically up the player's secondary resource by the new item's
		// bonus here, but for now new purchases do not increase the stat's
		// current value, only the maximum.
	}
	else
	{
		//@TODO Handle minion regen here.
	}
}

void UValorStatComponent::IncrementLevel()
{
	Experience = FMath::Max(Experience - ExperienceRequiredPerLevel[Level - 1], 0);
	check(++Level <= VALOR_MAX_CHARACTER_LEVEL);
}

void UValorStatComponent::OnItemPurchased()
{
	RecalculateStats(false, false);
}

void UValorStatComponent::OnRep_Health_Implementation()
{

}

void UValorStatComponent::OnRep_PrimaryResource_Implementation(){}

void UValorStatComponent::OnRep_SecondaryResource_Implementation(){}

void UValorStatComponent::OnRep_HealthRegen_Implementation(){}

void UValorStatComponent::OnRep_PrimaryResourceRegen_Implementation(){}

void UValorStatComponent::OnRep_SecondaryResourceRegen_Implementation(){}

void UValorStatComponent::OnRep_BonusHealth_Implementation(){}

void UValorStatComponent::OnRep_BonusPrimaryResource_Implementation(){}

void UValorStatComponent::OnRep_BonusSecondaryResource_Implementation(){}

void UValorStatComponent::OnRep_BonusHealthRegen_Implementation(){}

void UValorStatComponent::OnRep_BonusPrimaryResourceRegen_Implementation(){}

void UValorStatComponent::OnRep_BonusSecondaryResourceRegen_Implementation(){}

void UValorStatComponent::GetLifetimeReplicatedProps(TArray<FLifetimeProperty> & OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);

	DOREPLIFETIME(UValorStatComponent, Health);
	DOREPLIFETIME(UValorStatComponent, Level);
	DOREPLIFETIME(UValorStatComponent, Experience);
	DOREPLIFETIME(UValorStatComponent, PrimaryResource);
	DOREPLIFETIME(UValorStatComponent, SecondaryResource);
	DOREPLIFETIME(UValorStatComponent, HealthRegen);
	DOREPLIFETIME(UValorStatComponent, PrimaryResourceRegen);
	DOREPLIFETIME(UValorStatComponent, SecondaryResourceRegen);

	DOREPLIFETIME_CONDITION(UValorStatComponent, BonusHealth, COND_OwnerOnly);
	DOREPLIFETIME_CONDITION(UValorStatComponent, BonusPrimaryResource, COND_OwnerOnly);
	DOREPLIFETIME_CONDITION(UValorStatComponent, BonusSecondaryResource, COND_OwnerOnly);
	DOREPLIFETIME_CONDITION(UValorStatComponent, BonusHealthRegen, COND_OwnerOnly);
	DOREPLIFETIME_CONDITION(UValorStatComponent, BonusPrimaryResourceRegen, COND_OwnerOnly);
	DOREPLIFETIME_CONDITION(UValorStatComponent, BonusSecondaryResourceRegen, COND_OwnerOnly);
}

#undef ADD_STAT