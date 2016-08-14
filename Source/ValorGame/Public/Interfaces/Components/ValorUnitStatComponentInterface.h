// Copyright Shirasho Media 2016. All rights reserved.

#pragma once

#include "ValorTypes.h"
#include "ValorUnitStatComponentInterface.generated.h"

UINTERFACE(MinimalAPI)
class UValorUnitStatComponentInterface : public UInterface
{
	GENERATED_UINTERFACE_BODY()
};

class IValorUnitStatComponentInterface
{
	GENERATED_IINTERFACE_BODY()

	virtual float GetMana(EValorStatType StatType) const;
	virtual void SetMana(float Value);
	virtual void AdjustMana(float Value);
	virtual void AdjustBonusMana(float Value);

	virtual float GetManaRegen(EValorStatType StatType) const;
	virtual void AdjustBonusManaRegen(float Value);

	virtual float GetCooldownReduction(EValorStatType StatType) const;
	virtual void AdjustBonusCooldownReduction(float Value);

	virtual float GetMovementSpeed(EValorStatType StatType) const;
	virtual void AdjustBonusMovementSpeed(float Value);

	virtual int32 GetExperience() const;
	virtual void AdjustExperience(int32 Value);

	virtual uint8 GetUnitLevel() const;
	virtual void SetUnitLevel(uint8 Value);

	virtual void Initialize(const class AValorPlayerState* PlayerState);
};