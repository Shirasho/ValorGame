// Copyright Shirasho Media 2016. All rights reserved.

#pragma once

#include "ValorCharacter.h"
#include "ValorSpawnableInterface.h"
#include "ValorMinion.generated.h"

UCLASS(Abstract, NotBlueprintable, BlueprintType, NotPlaceable)
class AValorMinion : public AValorCharacter, public IValorSpawnableInterface
{
	GENERATED_UCLASS_BODY()

public:

	//virtual void PreInitializeComponents() override;

	//virtual void PostInitializeComponents() override;

	//virtual void BeginPlay() override;

	//virtual void EndPlay(const EEndPlayReason::Type EndPlayReason) override;

	//virtual void Tick(float DeltaSeconds) override;

public:

	/* Spawns a lane minion and initializes the character. */
	virtual void Spawn(APlayerState* UsePlayerState = nullptr, const FValorVariantData& ExtraData = FValorVariantData()) override;
	/* Spawns a lane minion and initializes the character. */
	virtual void Spawn(APlayerState* UsePlayerState = nullptr, void* ExtraData = nullptr) override;

protected:

	class AValorMinionController* MinionController;
};