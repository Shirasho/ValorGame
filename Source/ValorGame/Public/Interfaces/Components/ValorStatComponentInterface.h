// Copyright Shirasho Media 2016. All rights reserved.

#pragma once

#include "ValorTypes.h"
#include "ValorStatComponentInterface.generated.h"

UINTERFACE(MinimalAPI, BlueprintType, meta = (CannotImplementInterfaceInBlueprint))
class UValorStatComponentInterface : public UInterface
{
	GENERATED_UINTERFACE_BODY()
};

class IValorStatComponentInterface
{
	GENERATED_IINTERFACE_BODY()

	UFUNCTION(BlueprintCallable, Category = Stats)
	virtual float GetHealth(EValorStatType StatType) const;
	virtual void SetHealth(float Value);
	virtual void AdjustHealth(float Value);

	virtual void AdjustBonusHealth(float Value);

	/* Secondary resource won't be implemented here as it adds
	 * unnecessary bloat. Heroes or units that need it can extend
	 * ValorStatComponent (or ValorHeroStatComponent) and implement
	 * it where needed. */
	UFUNCTION(BlueprintCallable, Category = Stats)
	virtual float GetHealthRegen(EValorStatType StatType) const;
	virtual void AdjustBonusHealthRegen(float Value);

	UFUNCTION(BlueprintCallable, Category = Stats)
	virtual float GetPhysicalDamage(EValorStatType StatType) const;
	virtual void AdjustBonusPhysicalDamage(float Value);

	UFUNCTION(BlueprintCallable, Category = Stats)
	virtual float GetMagicalDamage(EValorStatType StatType) const;
	virtual void AdjustBonusMagicalDamage(float Value);

	UFUNCTION(BlueprintCallable, Category = Stats)
	virtual float GetPhysicalResist(EValorStatType StatType) const;
	virtual void AdjustBonusPhysicalResist(float Value);

	UFUNCTION(BlueprintCallable, Category = Stats)
	virtual float GetMagicalResist(EValorStatType StatType) const;
	virtual void AdjustBonusMagicalResist(float Value);

	UFUNCTION(BlueprintCallable, Category = Stats)
	virtual float GetAttackSpeed(EValorStatType StatType) const;
	virtual void AdjustBonusAttackSpeed(float Value);

	UFUNCTION(BlueprintCallable, Category = Stats)
	virtual float GetAttackRange(EValorStatType StatType) const;
	virtual void AdjustBonusAttackRange(float Value);

	virtual void Initialize(const class AValorPlayerState* PlayerState);
};