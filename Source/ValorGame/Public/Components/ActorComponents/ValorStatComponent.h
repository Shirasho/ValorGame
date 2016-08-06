// Copyright Shirasho Media 2016. All rights reserved.

#pragma once

#include "Components/ActorComponent.h"
#include "ValorStatComponentInterface.h"
#include "ValorStatComponent.generated.h"

UCLASS(Config=Game, ClassGroup=Valor, meta=(BlueprintSpawnableComponent, DisplayName="Stat Component (Generic)"))
class UValorStatComponent : public UActorComponent, public IValorStatComponentInterface
{
	GENERATED_UCLASS_BODY()

public:

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = Stats)
	const class UDataTable* StatTable;

	/* The number of times to recover the stats every 5 seconds. For example, a value of '20' will
	 * cause a tick every .25 seconds. */
	UPROPERTY(Config, EditDefaultsOnly, BlueprintReadOnly, Category = General)
	uint8 RecoverTickFrequency;

protected:

	UPROPERTY(BlueprintReadOnly, Replicated, Category = Stats)
	float Health;

	UPROPERTY(BlueprintReadOnly, Replicated, Category = Stats)
	float BonusHealth;

	UPROPERTY(BlueprintReadOnly, Replicated, Category = Stats)
	float BonusHealthRegen;

	UPROPERTY(BlueprintReadOnly, Replicated, Category = Stats)
	float BonusPhysicalDamage;

	UPROPERTY(BlueprintReadOnly, Replicated, Category = Stats)
	float BonusMagicalDamage;

	UPROPERTY(BlueprintReadOnly, Replicated, Category = Stats)
	float BonusPhysicalResist;

	UPROPERTY(BlueprintReadOnly, Replicated, Category = Stats)
	float BonusMagicalResist;

	UPROPERTY(Replicated)
	TArray<float> BaseHealthPerLevel;
	UPROPERTY(Replicated)
	TArray<float> BaseHealthRegenPerLevel;
	UPROPERTY(Replicated)
	TArray<float> BasePhysicalDamagePerLevel;
	UPROPERTY(Replicated)
	TArray<float> BaseMagicalDamagePerLevel;
	UPROPERTY(Replicated)
	TArray<float> BasePhysicalResistPerLevel;
	UPROPERTY(Replicated)
	TArray<float> BaseMagicalResistPerLevel;

private:

	FTimerHandle TimerHandle_RecoverStats;

public:

	virtual void BeginPlay() override;

public:

	UFUNCTION(BlueprintPure, Category = Stats)
	virtual float GetHealth(EValorStatType StatType) const;

	UFUNCTION(BlueprintCallable, Category = Stats)
	virtual void SetHealth(float Value);

	UFUNCTION(BlueprintCallable, Category = Stats)
	virtual void AdjustHealth(float Value);

	UFUNCTION(BlueprintCallable, Category = Stats)
	virtual void AdjustBonusHealth(float Value);

	/* Secondary resource won't be implemented here as it adds
	* unnecessary bloat. Heroes or units that need it can extend
	* ValorStatComponent (or ValorHeroStatComponent) and implement
	* it where needed. */

	UFUNCTION(BlueprintPure, Category = Stats)
	virtual float GetHealthRegen(EValorStatType StatType) const;

	UFUNCTION(BlueprintCallable, Category = Stats)
	virtual void AdjustBonusHealthRegen(float Value);


	UFUNCTION(BlueprintPure, Category = Stats)
	virtual float GetPhysicalDamage(EValorStatType StatType) const;

	UFUNCTION(BlueprintCallable, Category = Stats)
	virtual void AdjustBonusPhysicalDamage(float Value);


	UFUNCTION(BlueprintPure, Category = Stats)
	virtual float GetMagicalDamage(EValorStatType StatType) const;

	UFUNCTION(BlueprintCallable, Category = Stats)
	virtual void AdjustBonusMagicalDamage(float Value);


	UFUNCTION(BlueprintPure, Category = Stats)
	virtual float GetPhysicalResist(EValorStatType StatType) const;

	UFUNCTION(BlueprintCallable, Category = Stats)
	virtual void AdjustBonusPhysicalResist(float Value);


	UFUNCTION(BlueprintPure, Category = Stats)
	virtual float GetMagicalResist(EValorStatType StatType) const;

	UFUNCTION(BlueprintCallable, Category = Stats)
	virtual void AdjustBonusMagicalResist(float Value);

	virtual void Initialize(const class AValorPlayerState* PlayerState = nullptr);

protected:

	virtual void RecoverStats();
};
