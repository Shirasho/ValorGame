// Copyright Shirasho Media 2016. All rights reserved.

#pragma once

#include "ValorStatComponent.h"
#include "ValorUnitStatComponentInterface.h"
#include "ValorUnitStatComponent.generated.h"

UCLASS(ClassGroup = Valor, meta = (BlueprintSpawnableComponent, DisplayName = "Stat Component (Units)"))
class UValorUnitStatComponent : public UValorStatComponent, public IValorUnitStatComponentInterface
{
	GENERATED_UCLASS_BODY()

public:

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = Stats)
		const class UDataTable* ExperienceTable;

protected:

	UPROPERTY(BlueprintReadOnly, Replicated, Category = Stats)
		float Mana;
	UPROPERTY(BlueprintReadOnly, Replicated, Category = Stats)
		float BonusMana;

	UPROPERTY(BlueprintReadOnly, Replicated, Category = Stats)
		float BonusManaRegen;

	UPROPERTY(BlueprintReadOnly, Replicated, Category = Stats)
		float CooldownReduction;

	UPROPERTY(BlueprintReadOnly, Replicated, Category = Stats)
		float BonusMovementSpeed;

	UPROPERTY(BlueprintReadOnly, Replicated, Category = Stats)
		uint8 UnitLevel;

	UPROPERTY(BlueprintReadOnly, Replicated, Category = Stats)
		int32 Experience;

	UPROPERTY(Replicated)
	TArray<float> BaseManaPerLevel;
	UPROPERTY(Replicated)
	TArray<float> BaseManaRegenPerLevel;
	UPROPERTY(Replicated)
	TArray<float> BaseMovementSpeedPerLevel;
	UPROPERTY(Replicated)
	TArray<int32> RequiredExperiencePerLevel;

public:

	virtual void Initialize(const class AValorPlayerState* PlayerState = nullptr) override;

public:

	UFUNCTION(BlueprintCallable, Category = Stats)
	virtual float GetMana(EValorStatType StatType) const override;

	UFUNCTION(BlueprintCallable, Category = Stats)
	virtual void SetMana(float Value) override;

	UFUNCTION(BlueprintCallable, Category = Stats)
	virtual void AdjustMana(float Value) override;

	UFUNCTION(BlueprintCallable, Category = Stats)
	virtual void AdjustBonusMana(float Value) override;

	UFUNCTION(BlueprintCallable, Category = Stats)
	virtual float GetManaRegen(EValorStatType StatType) const override;

	UFUNCTION(BlueprintCallable, Category = Stats)
	virtual void AdjustBonusManaRegen(float Value) override;

	UFUNCTION(BlueprintCallable, Category = Stats)
	virtual float GetCooldownReduction(EValorStatType StatType) const override;

	UFUNCTION(BlueprintCallable, Category = Stats)
	virtual void AdjustBonusCooldownReduction(float Value) override;

	UFUNCTION(BlueprintCallable, Category = Stats)
	virtual float GetMovementSpeed(EValorStatType StatType) const override;

	UFUNCTION(BlueprintCallable, Category = Stats)
	virtual void AdjustBonusMovementSpeed(float Value) override;

	UFUNCTION(BlueprintCallable, Category = Stats)
	virtual int32 GetExperience() const override;

	UFUNCTION(BlueprintCallable, Category = Stats)
	virtual void AdjustExperience(int32 Value) override;

	UFUNCTION(BlueprintCallable, Category = Stats)
	virtual uint8 GetUnitLevel() const override;

	UFUNCTION(BlueprintCallable, Category = Stats)
	virtual void SetUnitLevel(uint8 Value) override;

	// ValorStatComponentInterface Overrides

	UFUNCTION(BlueprintCallable, Category = Stats)
	virtual float GetHealth(EValorStatType StatType) const override;

	UFUNCTION(BlueprintCallable, Category = Stats)
	virtual float GetHealthRegen(EValorStatType StatType) const override;

	UFUNCTION(BlueprintCallable, Category = Stats)
	virtual float GetPhysicalDamage(EValorStatType StatType) const override;

	UFUNCTION(BlueprintCallable, Category = Stats)
	virtual float GetMagicalDamage(EValorStatType StatType) const override;

	UFUNCTION(BlueprintCallable, Category = Stats)
	virtual float GetPhysicalResist(EValorStatType StatType) const override;

	UFUNCTION(BlueprintCallable, Category = Stats)
	virtual float GetMagicalResist(EValorStatType StatType) const override;

	UFUNCTION(BlueprintCallable, Category = Stats)
	virtual float GetAttackSpeed(EValorStatType StatType) const override;

	UFUNCTION(BlueprintCallable, Category = Stats)
	virtual float GetAttackRange(EValorStatType StatType) const override;

protected:
	
	virtual void RecoverStats() override;

protected:

	virtual void CheckForLevelUp();
};