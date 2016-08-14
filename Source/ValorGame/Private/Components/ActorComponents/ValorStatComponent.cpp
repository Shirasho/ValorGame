// Copyright Shirasho Media 2016. All rights reserved.

#include "ValorGame.h"
#include "ValorStatComponent.h"

#include "DataBlueprintLibrary.h"
#include "ValorDataDefinitions.h"
#include "ValorStatTableRow.h"

UValorStatComponent::UValorStatComponent(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer)
{
	bWantsBeginPlay = true;
	PrimaryComponentTick.bCanEverTick = false;
	PrimaryComponentTick.bStartWithTickEnabled = false;

	bAutoActivate = true;
	SetNetAddressable();
	SetIsReplicated(true);

	BonusHealth = 0.f;
	BonusHealthRegen = 0.f;
}

void UValorStatComponent::BeginPlay()
{
	Super::BeginPlay();

	if (StatTable)
	{
		ensure(StatTable->RowStruct->IsChildOf(FValorStatTableRow::StaticStruct()));
	}
	GetWorld()->GetTimerManager().SetTimer(TimerHandle_RecoverStats, this, &UValorStatComponent::RecoverStats, GetWorld()->GetWorldSettings()->GetEffectiveTimeDilation() * (5.f / RecoverTickFrequency), true);
}

void UValorStatComponent::Initialize(const class AValorPlayerState* PlayerState)
{
	if (StatTable)
	{
		const TArray<TArray<FString>>& StatTableData = StatTable->GetTableData();

		// Base Health
		{
			const TArray<FString>* CurrentStatLookupPtr = StatTableData.FindByPredicate([](const TArray<FString>& DataRow) { return DataRow.Num() > 0 && DataRow[0] == VALOR_DATA_ROW_BASE_HEALTH; });
			if (CurrentStatLookupPtr)
			{
				ensureMsgf(UDataBlueprintLibrary::ParseStringArray_float(*CurrentStatLookupPtr, BaseHealthPerLevel, 1), TEXT("Invalid data found in row '%s'."), *VALOR_DATA_ROW_BASE_HEALTH);
			}
		}
		// Base Health Regen
		{
			const TArray<FString>* CurrentStatLookupPtr = StatTableData.FindByPredicate([](const TArray<FString>& DataRow) { return DataRow.Num() > 0 && DataRow[0] == VALOR_DATA_ROW_BASE_HEALTH_REGEN; });
			if (CurrentStatLookupPtr)
			{
				ensureMsgf(UDataBlueprintLibrary::ParseStringArray_float(*CurrentStatLookupPtr, BaseHealthRegenPerLevel, 1), TEXT("Invalid data found in row '%s'."), *VALOR_DATA_ROW_BASE_HEALTH_REGEN);
			}
		}
		// Base Physical Damage
		{
			const TArray<FString>* CurrentStatLookupPtr = StatTableData.FindByPredicate([](const TArray<FString>& DataRow) { return DataRow.Num() > 0 && DataRow[0] == VALOR_DATA_ROW_BASE_PHYSICAL_DAMAGE; });
			if (CurrentStatLookupPtr)
			{
				ensureMsgf(UDataBlueprintLibrary::ParseStringArray_float(*CurrentStatLookupPtr, BasePhysicalDamagePerLevel, 1), TEXT("Invalid data found in row '%s'."), *VALOR_DATA_ROW_BASE_PHYSICAL_DAMAGE);
			}
		}
		// Base PhysicalResist
		{
			const TArray<FString>* CurrentStatLookupPtr = StatTableData.FindByPredicate([](const TArray<FString>& DataRow) { return DataRow.Num() > 0 && DataRow[0] == VALOR_DATA_ROW_BASE_PHYSICAL_RESIST; });
			if (CurrentStatLookupPtr)
			{
				ensureMsgf(UDataBlueprintLibrary::ParseStringArray_float(*CurrentStatLookupPtr, BasePhysicalResistPerLevel, 1), TEXT("Invalid data found in row '%s'."), *VALOR_DATA_ROW_BASE_PHYSICAL_RESIST);
			}
		}
		// Base Magical Damage
		{
			const TArray<FString>* CurrentStatLookupPtr = StatTableData.FindByPredicate([](const TArray<FString>& DataRow) { return DataRow.Num() > 0 && DataRow[0] == VALOR_DATA_ROW_BASE_MAGICAL_DAMAGE; });
			if (CurrentStatLookupPtr)
			{
				ensureMsgf(UDataBlueprintLibrary::ParseStringArray_float(*CurrentStatLookupPtr, BaseMagicalDamagePerLevel, 1), TEXT("Invalid data found in row '%s'."), *VALOR_DATA_ROW_BASE_MAGICAL_DAMAGE);
			}
		}
		// Base Magical Resist
		{
			const TArray<FString>* CurrentStatLookupPtr = StatTableData.FindByPredicate([](const TArray<FString>& DataRow) { return DataRow.Num() > 0 && DataRow[0] == VALOR_DATA_ROW_BASE_MAGICAL_RESIST; });
			if (CurrentStatLookupPtr)
			{
				ensureMsgf(UDataBlueprintLibrary::ParseStringArray_float(*CurrentStatLookupPtr, BaseMagicalResistPerLevel, 1), TEXT("Invalid data found in row '%s'."), *VALOR_DATA_ROW_BASE_MAGICAL_RESIST);
			}
		}
		// Base Attack Speed
		{
			const TArray<FString>* CurrentStatLookupPtr = StatTableData.FindByPredicate([](const TArray<FString>& DataRow) { return DataRow.Num() > 0 && DataRow[0] == VALOR_DATA_ROW_BASE_ATTACK_SPEED; });
			if (CurrentStatLookupPtr)
			{
				ensureMsgf(UDataBlueprintLibrary::ParseStringArray_float(*CurrentStatLookupPtr, BaseAttackSpeedPerLevel, 1), TEXT("Invalid data found in row '%s'."), *VALOR_DATA_ROW_BASE_ATTACK_SPEED);
			}
		}
		// Base Attack Range
		{
			const TArray<FString>* CurrentStatLookupPtr = StatTableData.FindByPredicate([](const TArray<FString>& DataRow) { return DataRow.Num() > 0 && DataRow[0] == VALOR_DATA_ROW_BASE_ATTACK_RANGE; });
			if (CurrentStatLookupPtr)
			{
				ensureMsgf(UDataBlueprintLibrary::ParseStringArray_float(*CurrentStatLookupPtr, BaseAttackRangePerLevel, 1), TEXT("Invalid data found in row '%s'."), *VALOR_DATA_ROW_BASE_ATTACK_RANGE);
			}
		}
	}

	Health = GetHealth(EValorStatType::Max);
}

void UValorStatComponent::RecoverStats()
{
	AdjustHealth(GetHealthRegen(EValorStatType::Current));
}

float UValorStatComponent::GetHealth(EValorStatType StatType) const
{
	// If you hit this it means the DataTable is missing the row or the appropriate number of columns.
	if (ensure(BaseHealthPerLevel.Num() > 0))
	{
		switch (StatType)
		{
			case EValorStatType::Base: return BaseHealthPerLevel[0];
			case EValorStatType::Bonus: return BonusHealth;
			case EValorStatType::Current: return Health;
			case EValorStatType::Max: return BaseHealthPerLevel[0] + BonusHealth;
		}
	}
	return 0.f;
}
void UValorStatComponent::SetHealth(float Value)
{
	Health = FMath::Clamp(Value, 0.f, GetHealth(EValorStatType::Max));
}
void UValorStatComponent::AdjustHealth(float Value)
{
 	Health = FMath::Clamp(Health + Value, 0.f, GetHealth(EValorStatType::Max));
}
void UValorStatComponent::AdjustBonusHealth(float Value)
{
	BonusHealth = FMath::Max(BonusHealth + Value, 0.f);
}

float UValorStatComponent::GetHealthRegen(EValorStatType StatType) const
{
	// If you hit this it means the DataTable is missing the row or the appropriate number of columns.
	if (ensure(BaseHealthRegenPerLevel.Num() > 0))
	{
		switch (StatType)
		{
			case EValorStatType::Base: return BaseHealthRegenPerLevel[0];
			case EValorStatType::Bonus: return BonusHealthRegen;
			case EValorStatType::Current: return BaseHealthRegenPerLevel[0] + BonusHealthRegen;
			case EValorStatType::Max: return -1; // Health regen has no maximum value.
		}
	}
	return 0.f;
}

void UValorStatComponent::AdjustBonusHealthRegen(float Value)
{
	BonusHealthRegen = FMath::Max(BonusHealthRegen + Value, 0.f);
}

float UValorStatComponent::GetPhysicalDamage(EValorStatType StatType) const
{
	// If you hit this it means the DataTable is missing the row or the appropriate number of columns.
	if (ensure(BasePhysicalDamagePerLevel.Num()))
	{
		switch (StatType)
		{
			case EValorStatType::Base: return BasePhysicalDamagePerLevel[0];
			case EValorStatType::Bonus: return BonusPhysicalDamage;
			case EValorStatType::Current: return BasePhysicalDamagePerLevel[0]+ BonusPhysicalDamage;
			case EValorStatType::Max: return -1; // Physical damage has no maximum value.
		}
	}
	
	return 0.f;
}

void UValorStatComponent::AdjustBonusPhysicalDamage(float Value)
{
	BonusPhysicalDamage = FMath::Max(BonusPhysicalDamage + Value, 0.f);
}

float UValorStatComponent::GetMagicalDamage(EValorStatType StatType) const
{
	// If you hit this it means the DataTable is missing the row or the appropriate number of columns.
	if (ensure(BaseMagicalDamagePerLevel.Num() > 0))
	{
		switch (StatType)
		{
			case EValorStatType::Base: return BaseMagicalDamagePerLevel[0];
			case EValorStatType::Bonus: return BonusMagicalDamage;
			case EValorStatType::Current: return BaseMagicalDamagePerLevel[0] + BonusMagicalDamage;
			case EValorStatType::Max: return -1; // Physical damage has no maximum value.
		}
	}

	return 0.f;
}

void UValorStatComponent::AdjustBonusMagicalDamage(float Value)
{
	BonusMagicalDamage = FMath::Max(BonusMagicalDamage + Value, 0.f);
}

float UValorStatComponent::GetPhysicalResist(EValorStatType StatType) const
{
	// If you hit this it means the DataTable is missing the row or the appropriate number of columns.
	if (ensure(BasePhysicalResistPerLevel.Num() > 0))
	{
		switch (StatType)
		{
			case EValorStatType::Base: return BasePhysicalResistPerLevel[0];
			case EValorStatType::Bonus: return BonusPhysicalResist;
			case EValorStatType::Current: return BasePhysicalResistPerLevel[0] + BonusPhysicalResist;
			case EValorStatType::Max: return -1; // Physical resist has no maximum value.
		}
	}

	return 0.f;
}
void UValorStatComponent::AdjustBonusPhysicalResist(float Value)
{
	BonusPhysicalResist = FMath::Max(BonusPhysicalResist + Value, 0.f);
}

float UValorStatComponent::GetMagicalResist(EValorStatType StatType) const
{
	// If you hit this it means the DataTable is missing the row or the appropriate number of columns.
	if (ensure(BaseMagicalResistPerLevel.Num() > 0))
	{
		switch (StatType)
		{
			case EValorStatType::Base: return BaseMagicalResistPerLevel[0];
			case EValorStatType::Bonus: return BonusMagicalResist;
			case EValorStatType::Current: return BaseMagicalResistPerLevel[0] + BonusMagicalResist;
			case EValorStatType::Max: return -1; // Magical resist has no maximum value.
		}
	}

	return 0.f;
}

void UValorStatComponent::AdjustBonusMagicalResist(float Value)
{
	BonusMagicalResist = FMath::Max(BonusMagicalResist + Value, 0.f);
}

float UValorStatComponent::GetAttackSpeed(EValorStatType StatType) const
{
	// If you hit this it means the DataTable is missing the row or the appropriate number of columns.
	if (ensure(BaseAttackSpeedPerLevel.Num() > 0))
	{
		switch (StatType)
		{
			case EValorStatType::Base: return BaseAttackSpeedPerLevel[0];
			case EValorStatType::Bonus: return BonusAttackSpeed;
			case EValorStatType::Current: return BaseAttackSpeedPerLevel[0] + BonusAttackSpeed;
			case EValorStatType::Max: return 2.f; // Magical resist has no maximum value.
		}
	}

	return 0.f;
}

void UValorStatComponent::AdjustBonusAttackSpeed(float Value)
{
	BonusAttackSpeed = FMath::Clamp(BonusAttackSpeed + Value, 0.f, GetAttackSpeed(EValorStatType::Max));
}

float UValorStatComponent::GetAttackRange(EValorStatType StatType) const
{
	// If you hit this it means the DataTable is missing the row or the appropriate number of columns.
	if (ensure(BaseAttackRangePerLevel.Num() > 0))
	{
		switch (StatType)
		{
			case EValorStatType::Base: return BaseAttackRangePerLevel[0];
			case EValorStatType::Bonus: return BonusAttackRange;
			case EValorStatType::Current: return BaseAttackRangePerLevel[0] + BonusAttackRange;
			case EValorStatType::Max: return -1; // Magical resist has no maximum value.
		}
	}

	return 0.f;
}

void UValorStatComponent::AdjustBonusAttackRange(float Value)
{
	BonusAttackRange = FMath::Max(BonusAttackRange + Value, 0.f);
}

void UValorStatComponent::GetLifetimeReplicatedProps(TArray<FLifetimeProperty> & OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);

	DOREPLIFETIME(UValorStatComponent, Health);
	DOREPLIFETIME(UValorStatComponent, BonusHealth);
	DOREPLIFETIME(UValorStatComponent, BonusHealthRegen);
	DOREPLIFETIME(UValorStatComponent, BonusPhysicalDamage);
	DOREPLIFETIME(UValorStatComponent, BonusMagicalDamage);
	DOREPLIFETIME(UValorStatComponent, BonusPhysicalResist);
	DOREPLIFETIME(UValorStatComponent, BonusMagicalResist);
	DOREPLIFETIME(UValorStatComponent, BonusAttackSpeed);
	DOREPLIFETIME(UValorStatComponent, BonusAttackRange);

	DOREPLIFETIME(UValorStatComponent, BaseHealthPerLevel);
	DOREPLIFETIME(UValorStatComponent, BaseHealthRegenPerLevel);
	DOREPLIFETIME(UValorStatComponent, BasePhysicalDamagePerLevel);
	DOREPLIFETIME(UValorStatComponent, BaseMagicalDamagePerLevel);
	DOREPLIFETIME(UValorStatComponent, BasePhysicalResistPerLevel);
	DOREPLIFETIME(UValorStatComponent, BaseMagicalResistPerLevel);
	DOREPLIFETIME(UValorStatComponent, BaseAttackSpeedPerLevel);
	DOREPLIFETIME(UValorStatComponent, BaseAttackRangePerLevel);
}