// Copyright Shirasho Media 2016. All rights reserved.

#pragma once

#include "ValorMainInterfaceWidget.h"
#include "ValorHeroInitializationProperties.generated.h"

USTRUCT(BlueprintType)
struct FValorHeroInitializationProperties
{
	GENERATED_USTRUCT_BODY()

public:

	/* The UValorMainInterfaceWidget class to use as the main user interface. */
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Visuals|GUI")
		TSubclassOf<UValorMainInterfaceWidget> MainUserInterface;

	/* A decal that projects to the cursor location. */
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Visuals|Cursor")
		UMaterialInterface* ClickCursorDecal;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Visuals|Particles")
		UParticleSystem* SpawnParticleTemplate;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Visuals|Particles")
		TAssetPtr<UParticleSystem> DeathParticleTemplate;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Audio|Spawn")
		USoundCue* SpawnSoundCue;


	FValorHeroInitializationProperties()
	{

	}
};