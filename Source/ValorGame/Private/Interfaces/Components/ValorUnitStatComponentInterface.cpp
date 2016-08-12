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

float IValorUnitStatComponentInterface::GetManaRegen(EValorStatType StatType) const
{
	return 0.f;
}
void IValorUnitStatComponentInterface::SetManaRegen(float Value)
{

}
void IValorUnitStatComponentInterface::AdjustManaRegen(float Value)
{

}

float IValorUnitStatComponentInterface::GetCooldownReduction(EValorStatType StatType) const
{
	return 0.f;
}
void IValorUnitStatComponentInterface::SetCooldownReduction(float Value)
{

}
void IValorUnitStatComponentInterface::AdjustCooldownReduction(float Value)
{

}

float IValorUnitStatComponentInterface::GetMovementSpeed(EValorStatType StatType) const
{
	return 0.f;
}
void IValorUnitStatComponentInterface::SetMovementSpeed(float Value)
{

}
void IValorUnitStatComponentInterface::AdjustMovementSpeed(float Value)
{

}

int32 IValorUnitStatComponentInterface::GetExperience() const
{
	return 0;
}
void IValorUnitStatComponentInterface::SetExperience(int32 Value)
{

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