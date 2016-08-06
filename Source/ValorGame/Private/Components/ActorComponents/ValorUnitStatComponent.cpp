// Copyright Shirasho Media 2016. All rights reserved.

#include "ValorGame.h"
#include "ValorUnitStatComponent.h"

#include "ValorPlayerState.h"
#include "ValorGameMode.h"
#include "DataBlueprintLibrary.h"
#include "ValorDataDefinitions.h"
#include "ValorStatTableRow.h"

UValorUnitStatComponent::UValorUnitStatComponent(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer)
{
	UnitLevel = 1;
	Experience = 0;
}

void UValorUnitStatComponent::Initialize(const class AValorPlayerState* PlayerState)
{
	// Should always be true since the actor is only created on the server.
	if (GetOwnerRole() == ROLE_Authority)
	{
		APawn* Owner = Cast<APawn>(GetOwner());
		if (Owner && Owner->PlayerState == nullptr)
		{
			Owner->PlayerState = const_cast<AValorPlayerState*>(PlayerState);
		}
		else
		{
			UE_LOG(LogValorCharacter, Log, TEXT("Attempting to overwrite a valid PlayerState via UValorUnitStatComponent: Owner - '%s'."), *GetNameSafe(Owner));
		}
	}

	Super::Initialize();

	if (StatTable)
	{
		const TArray<TArray<FString>>& StatTableData = StatTable->GetTableData();

		// Base Mana
		{
			const TArray<FString>* CurrentStatLookupPtr = StatTableData.FindByPredicate([](const TArray<FString>& DataRow) { return DataRow.Num() > 0 && DataRow[0] == VALOR_DATA_ROW_BASE_MANA; });
			if (CurrentStatLookupPtr)
			{
				ensureMsgf(UDataBlueprintLibrary::ParseStringArray_float(*CurrentStatLookupPtr, BaseManaPerLevel, 1), TEXT("Invalid data found in row '%s'."), *VALOR_DATA_ROW_BASE_MANA);
			}
		}
		// Base Mana Regen
		{
			const TArray<FString>* CurrentStatLookupPtr = StatTableData.FindByPredicate([](const TArray<FString>& DataRow) { return DataRow.Num() > 0 && DataRow[0] == VALOR_DATA_ROW_BASE_MANA_REGEN; });
			if (CurrentStatLookupPtr)
			{
				ensureMsgf(UDataBlueprintLibrary::ParseStringArray_float(*CurrentStatLookupPtr, BaseManaRegenPerLevel, 1), TEXT("Invalid data found in row '%s'."), *VALOR_DATA_ROW_BASE_MANA_REGEN);
			}
		}
		// Base Movement Speed
		{
			const TArray<FString>* CurrentStatLookupPtr = StatTableData.FindByPredicate([](const TArray<FString>& DataRow) { return DataRow.Num() > 0 && DataRow[0] == VALOR_DATA_ROW_BASE_MOVEMENT_SPEED; });
			if (CurrentStatLookupPtr)
			{
				ensureMsgf(UDataBlueprintLibrary::ParseStringArray_float(*CurrentStatLookupPtr, BaseManaRegenPerLevel, 1), TEXT("Invalid data found in row '%s'."), *VALOR_DATA_ROW_BASE_MOVEMENT_SPEED);
			}
		}
	}

	Mana = GetMana(EValorStatType::Max);

	if (ExperienceTable)
	{
		const TArray<TArray<FString>>& ExperienceTableData = ExperienceTable->GetTableData();

		// Experience Required Per Level
		{
			const TArray<FString>* CurrentStatLookupPtr = ExperienceTableData.FindByPredicate([](const TArray<FString>& DataRow) { return DataRow.Num() > 0 && DataRow[0] == VALOR_DATA_ROW_EXPERIENCE; });
			if (CurrentStatLookupPtr)
			{
				ensureMsgf(UDataBlueprintLibrary::ParseStringArray_int32(*CurrentStatLookupPtr, RequiredExperiencePerLevel, 1), TEXT("Invalid data found in row '%s'."), *VALOR_DATA_ROW_EXPERIENCE);
			}
		}
	}
}

void UValorUnitStatComponent::RecoverStats()
{
	Super::RecoverStats();
	AdjustMana(GetManaRegen(EValorStatType::Current));
}

float UValorUnitStatComponent::GetMana(EValorStatType StatType) const
{
	// If you hit this it means the DataTable is missing the row or the appropriate number of columns.
	if (ensure(BaseManaPerLevel.Num() > GetUnitLevel()))
	{
		switch (StatType)
		{
			case EValorStatType::Base: return BaseManaPerLevel[GetUnitLevel() - 1];
			case EValorStatType::Bonus: return BonusMana;
			case EValorStatType::Current: return Mana;
			case EValorStatType::Max: return BaseManaPerLevel[GetUnitLevel() - 1] + BonusMana;
		}
	}
	return 0.f;
}
void UValorUnitStatComponent::SetMana(float Value)
{
	Mana = FMath::Clamp(Value, 0.f, GetMana(EValorStatType::Max));
}
void UValorUnitStatComponent::AdjustMana(float Value)
{
	Mana = FMath::Clamp(Mana + Value, 0.f, GetMana(EValorStatType::Max));
}
void UValorUnitStatComponent::AdjustBonusMana(float Value)
{
	BonusMana = FMath::Max(BonusMana + Value, 0.f);
}

float UValorUnitStatComponent::GetManaRegen(EValorStatType StatType) const
{
	// If you hit this it means the DataTable is missing the row or the appropriate number of columns.
	if (ensure(BaseManaRegenPerLevel.Num() > GetUnitLevel()))
	{
		switch (StatType)
		{
			case EValorStatType::Base: return BaseManaRegenPerLevel[GetUnitLevel() - 1];
			case EValorStatType::Bonus: return BonusManaRegen;
			case EValorStatType::Current: return BaseManaRegenPerLevel[GetUnitLevel() - 1] + BonusManaRegen;
			case EValorStatType::Max: return -1; // Mana regen does not have a maximum value.
		}
	}
	return 0.f;
}
void UValorUnitStatComponent::AdjustBonusManaRegen(float Value)
{
	BonusManaRegen = FMath::Max(BonusManaRegen + Value, 0.f);
}

float UValorUnitStatComponent::GetCooldownReduction(EValorStatType StatType) const
{
	switch (StatType)
	{
		case EValorStatType::Base: return 0.f;
		case EValorStatType::Bonus: return CooldownReduction;
		case EValorStatType::Current: return CooldownReduction;
		case EValorStatType::Max: return 0.5f;
	}

	return 0.f;
}
void UValorUnitStatComponent::AdjustBonusCooldownReduction(float Value)
{
	CooldownReduction = FMath::Clamp(CooldownReduction + Value, 0.f, GetCooldownReduction(EValorStatType::Max));
}

float UValorUnitStatComponent::GetMovementSpeed(EValorStatType StatType) const
{
	// If you hit this it means the DataTable is missing the row or the appropriate number of columns.
	if (ensure(BaseMovementSpeedPerLevel.Num() > GetUnitLevel()))
	{
		switch (StatType)
		{
			case EValorStatType::Base: return BaseMovementSpeedPerLevel[GetUnitLevel() - 1];
			case EValorStatType::Bonus: return BonusMovementSpeed;
			case EValorStatType::Current: return BaseMovementSpeedPerLevel[GetUnitLevel() - 1] + CooldownReduction;
			case EValorStatType::Max: return -1; // Movement speed does not have a maximum value.
		}
	}
	return 0.f;
}
void UValorUnitStatComponent::AdjustBonusMovementSpeed(float Value)
{
	BonusMovementSpeed = FMath::Max(BonusMovementSpeed + Value, 0.f);
}

int32 UValorUnitStatComponent::GetExperience() const
{
	return Experience;
}
void UValorUnitStatComponent::AdjustExperience(int32 Value)
{
	Experience = FMath::Max(Experience + Value, 0);
	CheckForLevelUp();
}

uint8 UValorUnitStatComponent::GetUnitLevel() const
{
	return UnitLevel;
}

void UValorUnitStatComponent::SetUnitLevel(uint8 Value)
{
	UnitLevel = Value;
}

void UValorUnitStatComponent::CheckForLevelUp()
{
	const AValorGameMode* GameMode = GetWorld()->GetAuthGameMode<AValorGameMode>();

	// Must be true for server.
	check(GameMode);

	uint8 MaxUnitLevel = GameMode->GetMaximumLevel();

	// We might give more experience than a single level's worth.
	// Keep going until we hit.
	while (UnitLevel < MaxUnitLevel && RequiredExperiencePerLevel.IsValidIndex(UnitLevel-1) && Experience >= RequiredExperiencePerLevel[UnitLevel-1])
	{
		AdjustExperience(-RequiredExperiencePerLevel[GetUnitLevel()-1]);
		++UnitLevel;
	}
}

void UValorUnitStatComponent::GetLifetimeReplicatedProps(TArray<FLifetimeProperty> & OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);

	DOREPLIFETIME(UValorUnitStatComponent, Mana);
	DOREPLIFETIME(UValorUnitStatComponent, BonusMana);
	DOREPLIFETIME(UValorUnitStatComponent, BonusManaRegen);
	DOREPLIFETIME(UValorUnitStatComponent, CooldownReduction);
	DOREPLIFETIME(UValorUnitStatComponent, BonusMovementSpeed);
	DOREPLIFETIME(UValorUnitStatComponent, UnitLevel);
	DOREPLIFETIME(UValorUnitStatComponent, Experience);

	DOREPLIFETIME(UValorUnitStatComponent, BaseManaPerLevel);
	DOREPLIFETIME(UValorUnitStatComponent, BaseManaRegenPerLevel);
	DOREPLIFETIME(UValorUnitStatComponent, BaseMovementSpeedPerLevel);
	DOREPLIFETIME(UValorUnitStatComponent, RequiredExperiencePerLevel);
}