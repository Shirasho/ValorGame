// Copyright Shirasho Media 2016. All rights reserved.

#pragma once

#include "ValorEngine.generated.h"

UCLASS()
class VALORGAME_API UValorEngine : public UGameEngine
{
    GENERATED_BODY()

public:

    /* Hook up the necessary callbacks. */
    virtual void Init(IEngineLoop* InEngineLoop) override;
};