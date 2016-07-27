// Copyright Shirasho Media 2016. All rights reserved.

#pragma once

#include "Engine/LevelScriptActor.h"
#include "ValorLevelScriptActor.generated.h"

/* An extended version of a Level Blueprint. */
UCLASS()
class AValorLevelScriptActor : public ALevelScriptActor
{
	GENERATED_UCLASS_BODY()

public:

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = ValorLevel)
		FName ValorLevelName;

public:

	//virtual void PreInitializeComponents() override;

	//virtual void PostInitializeComponents() override;

	//virtual void BeginPlay() override;

	//virtual void EndPlay(const EEndPlayReason::Type EndPlayReason) override;

	//virtual void Tick(float DeltaSeconds) override;
};