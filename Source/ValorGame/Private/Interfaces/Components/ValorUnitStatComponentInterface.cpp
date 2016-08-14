// Copyright Shirasho Media 2016. All rights reserved.

#include "ValorGame.h"
#include "ValorUnitStatComponentInterface.h"

UValorUnitStatComponentInterface::UValorUnitStatComponentInterface(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer)
{

}

float IValorUnitStatComponentInterface::GetMana(EValorStatType StatType) const
{
	return 0.f;
}
void IValorUnitStatComponentInterface::SetMana(float Value)
{

}
void IValorUnitStatComponentInterface::AdjustMana(float Value)
{

}
void IValorUnitStatComponentInterface::AdjustBonusMana(float Value)
{

}

float IValorUnitStatComponentInterface::GetManaRegen(EValorStatType StatType) const
{
	return 0.f;
}
void IValorUnitStatComponentInterface::AdjustBonusManaRegen(float Value)
{

}

float IValorUnitStatComponentInterface::GetCooldownReduction(EValorStatType StatType) const
{
	return 0.f;
}
void IValorUnitStatComponentInterface::AdjustBonusCooldownReduction(float Value)
{

}

float IValorUnitStatComponentInterface::GetMovementSpeed(EValorStatType StatType) const
{
	return 0.f;
}
void IValorUnitStatComponentInterface::AdjustBonusMovementSpeed(float Value)
{

}

int32 IValorUnitStatComponentInterface::GetExperience() const
{
	return 0;
}
void IValorUnitStatComponentInterface::AdjustExperience(int32 Value)
{

}

uint8 IValorUnitStatComponentInterface::GetUnitLevel() const
{
	return 1;
}
void IValorUnitStatComponentInterface::SetUnitLevel(uint8 Value)
{

}

void IValorUnitStatComponentInterface::Initialize(const class AValorPlayerState* PlayerState)
{

}