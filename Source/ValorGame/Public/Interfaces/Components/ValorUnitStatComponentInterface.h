// Copyright Shirasho Media 2016. All rights reserved.

#pragma once

#include "ValorTypes.h"
#include "ValorUnitStatComponentInterface.generated.h"

UINTERFACE(MinimalAPI, BlueprintType, meta = (CannotImplementInterfaceInBlueprint))
class UValorUnitStatComponentInterface : public UInterface
{
	GENERATED_UINTERFACE_BODY()
};

class IValorUnitStatComponentInterface
{
	GENERATED_IINTERFACE_BODY()

	UFUNCTION(BlueprintCallable, Category = Stats)
	virtual float GetMana(EValorStatType StatType) const;
	virtual void SetMana(float Value);
	virtual void AdjustMana(float Value);
	virtual void AdjustBonusMana(float Value);

	UFUNCTION(BlueprintCallable, Category = Stats)
	virtual float GetManaRegen(EValorStatType StatType) const;
	virtual void AdjustBonusManaRegen(float Value);

	UFUNCTION(BlueprintCallable, Category = Stats)
	virtual float GetCooldownReduction(EValorStatType StatType) const;
	virtual void AdjustBonusCooldownReduction(float Value);

	UFUNCTION(BlueprintCallable, Category = Stats)
	virtual float GetMovementSpeed(EValorStatType StatType) const;
	virtual void AdjustBonusMovementSpeed(float Value);

	UFUNCTION(BlueprintCallable, Category = Stats)
	virtual int32 GetExperience() const;
	virtual void AdjustExperience(int32 Value);

	UFUNCTION(BlueprintCallable, Category = Stats)
	virtual uint8 GetUnitLevel() const;
	virtual void SetUnitLevel(uint8 Value);

	virtual void Initialize(const class AValorPlayerState* PlayerState);
};