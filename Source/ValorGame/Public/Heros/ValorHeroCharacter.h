// Copyright Shirasho Media 2016. All rights reserved.

#pragma once

#include "ValorCharacter.h"
#include "ValorHeroCharacter.generated.h"

UCLASS(Abstract)
class AValorHeroCharacter : public AValorCharacter
{
	GENERATED_UCLASS_BODY()

public:

	/* A decal that projects to the cursor location. */
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = Camera, meta = (AllowPrivateAccess = "true"))
	UMaterialInterface* MovementCursorDecal;

public:

	virtual void PostInitializeComponents() override;

	virtual void BeginPlay() override;

	virtual void Tick(float DeltaSeconds) override;
};