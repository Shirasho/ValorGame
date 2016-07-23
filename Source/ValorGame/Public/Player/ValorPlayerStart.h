// Copyright Shirasho Media 2016. All rights reserved.

#pragma once

#include "ValorTypes.h"
#include "ValorPlayerStart.generated.h"

UCLASS()
class AValorPlayerStart : public APlayerStart
{
    GENERATED_BODY()

public:

    /* Which team(s) can spawn at this point. */
    UPROPERTY(EditInstanceOnly, meta = (BitMask, BitMaskEnum = EValorTeam), Category = Team)
    uint8 SpawnTeam;

    /* Whether players can spawn at this point. */
    UPROPERTY(EditInstanceOnly, Category = Team)
    bool bCanSpawnPlayers;

    /* Whether minions can spawn at this point. */
    UPROPERTY(EditInstanceOnly, Category = Team)
    bool bCanSpawnMinions;
};
