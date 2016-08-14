// Copyright Shirasho Media 2016. All rights reserved.

#include "ValorGame.h"
#include "ValorStatComponentInterface.h"

UValorStatComponentInterface::UValorStatComponentInterface(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer)
{

}

float IValorStatComponentInterface::GetHealth(EValorStatType StatType) const
{
	return 0.f;
}
void IValorStatComponentInterface::SetHealth(float Value)
{

}
void IValorStatComponentInterface::AdjustHealth(float Value)
{

}
void IValorStatComponentInterface::AdjustBonusHealth(float Value)
{

}

float IValorStatComponentInterface::GetHealthRegen(EValorStatType StatType) const
{
	return 0.f;
}
void IValorStatComponentInterface::AdjustBonusHealthRegen(float Value)
{

}

float IValorStatComponentInterface::GetPhysicalDamage(EValorStatType StatType) const
{
	return 0.f;
}
void IValorStatComponentInterface::AdjustBonusPhysicalDamage(float Value)
{

}

float IValorStatComponentInterface::GetMagicalDamage(EValorStatType StatType) const
{
	return 0.f;
}
void IValorStatComponentInterface::AdjustBonusMagicalDamage(float Value)
{

}

float IValorStatComponentInterface::GetPhysicalResist(EValorStatType StatType) const
{
	return 0.f;
}
void IValorStatComponentInterface::AdjustBonusPhysicalResist(float Value)
{

}

float IValorStatComponentInterface::GetMagicalResist(EValorStatType StatType) const
{
	return 0.f;
}
void IValorStatComponentInterface::AdjustBonusMagicalResist(float Value)
{

}

float IValorStatComponentInterface::GetAttackSpeed(EValorStatType StatType) const
{
	return 0.f;
}
void IValorStatComponentInterface::AdjustBonusAttackSpeed(float Value)
{
	
}

float IValorStatComponentInterface::GetAttackRange(EValorStatType StatType) const
{
	return 0.f;
}
void IValorStatComponentInterface::AdjustBonusAttackRange(float Value)
{

}

void IValorStatComponentInterface::Initialize(const class AValorPlayerState* PlayerState)
{

}