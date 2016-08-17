// Copyright Shirasho Media 2016. All rights reserved.

#pragma once

#include "ValorGameSingleton.generated.h"

UCLASS()
class VALORGAME_API UValorGameSingleton : public UObject
{
	GENERATED_UCLASS_BODY()

private:

	UPROPERTY(Replicated)
	uint32 bRelicationFlag : 1;
	
public:

	virtual bool IsSupportedForNetworking() const override
	{
		return true;
	}

public:

	UFUNCTION(BlueprintCallable, NetMulticast, Unreliable, meta = (AdvancedDisplay = "3", UnsafeDuringActorConstruction = "true"), Category = Sound)
		void MulticastPlaySoundAtLocation(UObject* WorldContextObject, class USoundBase* Sound, FVector Location, FRotator Rotation, float VolumeMultiplier = 1.f, float PitchMultiplier = 1.f, float StartTime = 0.f, class USoundAttenuation* AttenuationSettings = nullptr, class USoundConcurrency* ConcurrencySettings = nullptr);

protected:

	/**
	* Plays a sound at the given location. This is a fire and forget sound and does not travel with any actor.
	* @param Sound - sound to play
	* @param Location - World position to play sound at
	* @param Rotation - World rotation to play sound at
	* @param VolumeMultiplier - Volume multiplier
	* @param PitchMultiplier - PitchMultiplier
	* @param StartTime - How far in to the sound to begin playback at
	* @param AttenuationSettings - Override attenuation settings package to play sound with
	* @param ConcurrencySettings - Override concurrency settings package to play sound with
	*/
	/*void PlaySoundAtLocation(class USoundBase* Sound, FVector Location, FRotator Rotation, float VolumeMultiplier = 1.f, float PitchMultiplier = 1.f, float StartTime = 0.f, class USoundAttenuation* AttenuationSettings = nullptr, class USoundConcurrency* ConcurrencySettings = nullptr);

	void PlaySoundAtLocation(class USoundBase* Sound, FVector Location, float VolumeMultiplier = 1.f, float PitchMultiplier = 1.f, float StartTime = 0.f, class USoundAttenuation* AttenuationSettings = nullptr, class USoundConcurrency* ConcurrencySettings = nullptr)
	{
		PlaySoundAtLocation(Sound, Location, FRotator::ZeroRotator, VolumeMultiplier, PitchMultiplier, StartTime, AttenuationSettings, ConcurrencySettings);
	}*/
	
};
