// Copyright Shirasho Media 2016. All rights reserved.

#include "ValorGame.h"
#include "ValorSoundNodeLocalPlayer.h"

void UValorSoundNodeLocalPlayer::ParseNodes(FAudioDevice* AudioDevice, const UPTRINT NodeWaveInstanceHash, FActiveSound& ActiveSound, const FSoundParseParameters& ParseParams, TArray<FWaveInstance*>& WaveInstances)
{
    // The accesses to the Pawn will be unsafe once we thread audio, deal with this at that point
    check(IsInGameThread());

    UAudioComponent* AudioComponent = ActiveSound.GetAudioComponent();
    AActor* SoundOwner = AudioComponent ? AudioComponent->GetOwner() : nullptr;
    APlayerController* PlayerController = Cast<APlayerController>(SoundOwner);
    APawn* PawnOwner = (PlayerController ? PlayerController->GetPawn() : Cast<APawn>(SoundOwner));

    const bool bLocallyControlled = PawnOwner && PawnOwner->IsLocallyControlled() && Cast<APlayerController>(PawnOwner->Controller);
    const int32 PlayIndex = bLocallyControlled ? 0 : 1;

    if (PlayIndex < ChildNodes.Num() && ChildNodes[PlayIndex])
    {
        ChildNodes[PlayIndex]->ParseNodes(AudioDevice, GetNodeWaveInstanceHash(NodeWaveInstanceHash, ChildNodes[PlayIndex], PlayIndex), ActiveSound, ParseParams, WaveInstances);
    }
}

#if WITH_EDITOR
FText UValorSoundNodeLocalPlayer::GetInputPinName(int32 PinIndex) const
{
    return (PinIndex == 0) ? NSLOCTEXT("ValorGame.Core", "Local", "Local") : NSLOCTEXT("ValorGame.Core", "Remote", "Remote");
}
#endif

int32 UValorSoundNodeLocalPlayer::GetMaxChildNodes() const
{
    return 2;
}

int32 UValorSoundNodeLocalPlayer::GetMinChildNodes() const
{
    return 2;
}