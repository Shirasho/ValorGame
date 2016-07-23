// Copyright Shirasho Media 2016. All rights reserved.

#pragma once

#include "Sound/SoundNode.h"
#include "ValorSoundNodeLocalPlayer.generated.h"

UCLASS(HideCategories=Object, EditInlineNew)
class UValorSoundNodeLocalPlayer : public USoundNode
{
    GENERATED_BODY()

public:

    /** USOUNDNODE INTERFACE */
    virtual void ParseNodes(FAudioDevice* AudioDevice, const UPTRINT NodeWaveInstanceHash, FActiveSound& ActiveSound, const FSoundParseParameters& ParseParams, TArray<FWaveInstance*>& WaveInstances) override;
    virtual int32 GetMaxChildNodes() const override;
    virtual int32 GetMinChildNodes() const override;
#if WITH_EDITOR
    virtual FText GetInputPinName(int32 PinIndex) const override;
#endif
};