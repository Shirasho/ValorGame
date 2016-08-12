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

	virtual float GetManaRegen(EValorStatType StatType) const;
	virtual void SetManaRegen(float Value);
	virtual void AdjustManaRegen(float Value);

	virtual float GetCooldownReduction(EValorStatType StatType) const;
	virtual void SetCooldownReduction(float Value);
	virtual void AdjustCooldownReduction(float Value);

	virtual float GetMovementSpeed(EValorStatType StatType) const;
	virtual void SetMovementSpeed(float Value);
	virtual void AdjustMovementSpeed(float Value);

	virtual int32 GetExperience() const;
	virtual void SetExperience(int32 Value);
	virtual void AdjustExperience(int32 Value);

	virtual uint8 GetUnitLevel() const;
	virtual void SetUnitLevel(uint8 Value);

	virtual void Initialize(const class AValorPlayerState* PlayerState);
};