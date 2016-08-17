// Copyright Shirasho Media 2016. All rights reserved.

#pragma once

#include "ValorTypes.h"
#include "ValorUnitInterface.generated.h"

UINTERFACE(MinimalAPI, BlueprintType, meta=(CannotImplementInterfaceInBlueprint))
class UValorUnitInterface : public UInterface
{
	GENERATED_UINTERFACE_BODY()
};

class IValorUnitInterface
{
	GENERATED_IINTERFACE_BODY()

	UFUNCTION(BlueprintCallable, Category = Stats)
	virtual EValorTeam GetTeam() const;
	UFUNCTION(BlueprintCallable, Category = Stats)
	virtual class UValorStatComponent* GetStatComponent() const;

	UFUNCTION(BlueprintCallable, Category = UnitInterface)
	virtual bool IsStealthed() const;
	UFUNCTION(BlueprintCallable, Category = UnitInterface)
	virtual bool IsAlive() const;
	
};