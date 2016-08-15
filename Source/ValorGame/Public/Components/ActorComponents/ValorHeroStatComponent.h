// Copyright Shirasho Media 2016. All rights reserved.

#pragma once

#include "ValorUnitStatComponent.h"
#include "ValorHeroStatComponent.generated.h"

UCLASS(ClassGroup = Valor, meta = (BlueprintSpawnableComponent, DisplayName = "Stat Component (Heroes)"))
class UValorHeroStatComponent : public UValorUnitStatComponent
{
	GENERATED_UCLASS_BODY()

public:

	UFUNCTION(BlueprintCallable, Category = Stats)
	virtual int32 GetExperience() const override;

	UFUNCTION(BlueprintCallable, Category = Stats)
	virtual void AdjustExperience(int32 Value) override;

	UFUNCTION(BlueprintCallable, Category = Stats)
	virtual uint8 GetUnitLevel() const override;

	virtual void Initialize(const class AValorPlayerState* PlayerState = nullptr);
};