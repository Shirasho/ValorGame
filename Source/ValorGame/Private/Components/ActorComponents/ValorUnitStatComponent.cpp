// Copyright Shirasho Media 2016. All rights reserved.

#include "ValorGame.h"
#include "ValorUnitStatComponent.h"

#include "ValorPlayerState.h"
#include "ValorGameMode.h"
#include "TypesBlueprintLibrary.h"
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

	{
		DECLARE_SCOPE_CYCLE_COUNTER(TEXT("UValorUnitStatComponent::Initialize"), STAT_ValorUnitStatComponent_Initialize, STATGROUP_ValorComponent);

		Super::Initialize();

		if (StatTable)
		{
			const TArray<TArray<FString>>& StatTableData = StatTable->GetTableData();

			// Base Mana
			{
				const TArray<FString>* CurrentStatLookupPtr = StatTableData.FindByPredicate([](const TArray<FString>& DataRow) { return DataRow.Num() > 0 && DataRow[0] == VALOR_DATA_ROW_BASE_MANA; });
				if (CurrentStatLookupPtr)
				{
					ensureMsgf(UTypesBlueprintLibrary::K2_StringToFloatArray(*CurrentStatLookupPtr, BaseManaPerLevel, 1), TEXT("Invalid data found in row '%s'."), *VALOR_DATA_ROW_BASE_MANA);
				}
			}
			// Base Mana Regen
			{
				const TArray<FString>* CurrentStatLookupPtr = StatTableData.FindByPredicate([](const TArray<FString>& DataRow) { return DataRow.Num() > 0 && DataRow[0] == VALOR_DATA_ROW_BASE_MANA_REGEN; });
				if (CurrentStatLookupPtr)
				{
					ensureMsgf(UTypesBlueprintLibrary::K2_StringToFloatArray(*CurrentStatLookupPtr, BaseManaRegenPerLevel, 1), TEXT("Invalid data found in row '%s'."), *VALOR_DATA_ROW_BASE_MANA_REGEN);
				}
			}
			// Base Movement Speed
			{
				const TArray<FString>* CurrentStatLookupPtr = StatTableData.FindByPredicate([](const TArray<FString>& DataRow) { return DataRow.Num() > 0 && DataRow[0] == VALOR_DATA_ROW_BASE_MOVEMENT_SPEED; });
				if (CurrentStatLookupPtr)
				{
					ensureMsgf(UTypesBlueprintLibrary::K2_StringToFloatArray(*CurrentStatLookupPtr, BaseManaRegenPerLevel, 1), TEXT("Invalid data found in row '%s'."), *VALOR_DATA_ROW_BASE_MOVEMENT_SPEED);
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
					ensureMsgf(UTypesBlueprintLibrary::K2_StringToInt32Array(*CurrentStatLookupPtr, RequiredExperiencePerLevel, 1), TEXT("Invalid data found in row '%s'."), *VALOR_DATA_ROW_EXPERIENCE);
				}
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
	if (ensure(BaseManaPerLevel.IsValidIndex(GetUnitLevel()-1)))
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
	if (ensure(BaseManaRegenPerLevel.IsValidIndex(GetUnitLevel()-1)))
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
	if (ensure(BaseMovementSpeedPerLevel.IsValidIndex(GetUnitLevel()-1)))
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

float UValorUnitStatComponent::GetHealth(EValorStatType StatType) const
{
	// If you hit this it means the DataTable is missing the row or the appropriate number of columns.
	if (ensure(BaseHealthPerLevel.IsValidIndex(GetUnitLevel()-1)))
	{
		switch (StatType)
		{
			case EValorStatType::Base: return BaseHealthPerLevel[GetUnitLevel()-1];
			case EValorStatType::Bonus: return BonusHealth;
			case EValorStatType::Current: return Health;
			case EValorStatType::Max: return BaseHealthPerLevel[GetUnitLevel() - 1] + BonusHealth;
		}
	}
	return 0.f;
}

float UValorUnitStatComponent::GetHealthRegen(EValorStatType StatType) const
{
	// If you hit this it means the DataTable is missing the row or the appropriate number of columns.
	if (ensure(BaseHealthRegenPerLevel.IsValidIndex(GetUnitLevel()-1)))
	{
		switch (StatType)
		{
			case EValorStatType::Base: return BaseHealthRegenPerLevel[GetUnitLevel() - 1];
			case EValorStatType::Bonus: return BonusHealthRegen;
			case EValorStatType::Current: return BaseHealthRegenPerLevel[GetUnitLevel() - 1] + BonusHealthRegen;
			case EValorStatType::Max: return -1; // Health regen has no maximum value.
		}
	}
	return 0.f;
}

float UValorUnitStatComponent::GetPhysicalDamage(EValorStatType StatType) const
{
	// If you hit this it means the DataTable is missing the row or the appropriate number of columns.
	if (ensure(BasePhysicalDamagePerLevel.Num()))
	{
		switch (StatType)
		{
			case EValorStatType::Base: return BasePhysicalDamagePerLevel[GetUnitLevel() - 1];
			case EValorStatType::Bonus: return BonusPhysicalDamage;
			case EValorStatType::Current: return BasePhysicalDamagePerLevel[GetUnitLevel() - 1] + BonusPhysicalDamage;
			case EValorStatType::Max: return -1; // Physical damage has no maximum value.
		}
	}

	return 0.f;
}

float UValorUnitStatComponent::GetMagicalDamage(EValorStatType StatType) const
{
	// If you hit this it means the DataTable is missing the row or the appropriate number of columns.
	if (ensure(BaseMagicalDamagePerLevel.IsValidIndex(GetUnitLevel()-1)))
	{
		switch (StatType)
		{
			case EValorStatType::Base: return BaseMagicalDamagePerLevel[GetUnitLevel() - 1];
			case EValorStatType::Bonus: return BonusMagicalDamage;
			case EValorStatType::Current: return BaseMagicalDamagePerLevel[GetUnitLevel() - 1] + BonusMagicalDamage;
			case EValorStatType::Max: return -1; // Physical damage has no maximum value.
		}
	}

	return 0.f;
}

float UValorUnitStatComponent::GetPhysicalResist(EValorStatType StatType) const
{
	// If you hit this it means the DataTable is missing the row or the appropriate number of columns.
	if (ensure(BasePhysicalResistPerLevel.IsValidIndex(GetUnitLevel()-1)))
	{
		switch (StatType)
		{
			case EValorStatType::Base: return BasePhysicalResistPerLevel[GetUnitLevel() - 1];
			case EValorStatType::Bonus: return BonusPhysicalResist;
			case EValorStatType::Current: return BasePhysicalResistPerLevel[GetUnitLevel() - 1] + BonusPhysicalResist;
			case EValorStatType::Max: return -1; // Physical resist has no maximum value.
		}
	}

	return 0.f;
}

float UValorUnitStatComponent::GetMagicalResist(EValorStatType StatType) const
{
	// If you hit this it means the DataTable is missing the row or the appropriate number of columns.
	if (ensure(BaseMagicalResistPerLevel.IsValidIndex(GetUnitLevel()-1)))
	{
		switch (StatType)
		{
			case EValorStatType::Base: return BaseMagicalResistPerLevel[GetUnitLevel() - 1];
			case EValorStatType::Bonus: return BonusMagicalResist;
			case EValorStatType::Current: return BaseMagicalResistPerLevel[GetUnitLevel() - 1] + BonusMagicalResist;
			case EValorStatType::Max: return -1; // Magical resist has no maximum value.
		}
	}

	return 0.f;
}

float UValorUnitStatComponent::GetAttackSpeed(EValorStatType StatType) const
{
	// If you hit this it means the DataTable is missing the row or the appropriate number of columns.
	if (ensure(BaseAttackSpeedPerLevel.IsValidIndex(GetUnitLevel()-1)))
	{
		switch (StatType)
		{
			case EValorStatType::Base: return BaseAttackSpeedPerLevel[GetUnitLevel() - 1];
			case EValorStatType::Bonus: return BonusAttackSpeed;
			case EValorStatType::Current: return BaseAttackSpeedPerLevel[GetUnitLevel() - 1] + BonusAttackSpeed;
			case EValorStatType::Max: return 2.f; // Magical resist has no maximum value.
		}
	}

	return 0.f;
}

float UValorUnitStatComponent::GetAttackRange(EValorStatType StatType) const
{
	// If you hit this it means the DataTable is missing the row or the appropriate number of columns.
	if (ensure(BaseAttackRangePerLevel.IsValidIndex(GetUnitLevel()-1)))
	{
		switch (StatType)
		{
			case EValorStatType::Base: return BaseAttackRangePerLevel[GetUnitLevel() - 1];
			case EValorStatType::Bonus: return BonusAttackRange;
			case EValorStatType::Current: return BaseAttackRangePerLevel[GetUnitLevel() - 1] + BonusAttackRange;
			case EValorStatType::Max: return -1; // Magical resist has no maximum value.
		}
	}

	return 0.f;
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