// Copyright Shirasho Media 2016. All rights reserved.

#pragma once

#include "ValorTypes.h"
#include "ValorPlayerStart.generated.h"

UCLASS(ClassGroup=Valor)
class AValorPlayerStart : public APlayerStart
{
    GENERATED_BODY()

public:

	//virtual void PreInitializeComponents() override;

	//virtual void PostInitializeComponents() override;

	//virtual void BeginPlay() override;

	//virtual void EndPlay(const EEndPlayReason::Type EndPlayReason) override;

	//virtual void Tick(float DeltaSeconds) override;

public:

    /* Which team(s) can spawn at this point. */
    UPROPERTY(EditInstanceOnly, meta = (BitMask, BitMaskEnum = EValorTeam), Category = Team)
    uint8 SpawnTeam;
};
