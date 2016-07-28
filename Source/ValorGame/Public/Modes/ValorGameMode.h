// Copyright Shirasho Media 2016. All rights reserved.

#pragma once

#include "ValorGameMode.generated.h"


UCLASS(Config=Game)
class AValorGameMode : public AGameMode
{
	GENERATED_UCLASS_BODY()

protected:

	UPROPERTY(Config)
		int32 LaneMinionStartTime;

	UPROPERTY(Config)
		int32 LaneMinionWaveInterval;

	UPROPERTY(Config)
		int32 JungleMinionStartTime;

private:

	FTimerHandle TimerHandle_LaneMinion;
	FTimerHandle TimerHandle_JungleMinion;

public:

	//virtual void PreInitializeComponents() override;

	//virtual void PostInitializeComponents() override;

	virtual void BeginPlay() override;

	virtual void EndPlay(const EEndPlayReason::Type EndPlayReason) override;

	//virtual void Tick(float DeltaSeconds) override;

	/* Returns the game session class to use. */
	virtual TSubclassOf<AGameSession> GetGameSessionClass() const override;

	/* Determine which PlayerStart a player can spawn at. */
	virtual AActor* ChoosePlayerStart_Implementation(AController* Player) override;

	/* Returns the pawn class to use with the specified controller. */
	virtual UClass* GetDefaultPawnClassForController_Implementation(AController* InController) override;

	/* Whether cheats are allowed. */
	virtual bool AllowCheats(APlayerController* P) override;

protected:

	/* Check if player can use this PlayerStart. */
	virtual bool IsPlayerStartAllowed(APlayerStart* SpawnPoint, AController* Player) const;

	/* Check if player should use PlayerStart. */
	virtual bool IsPlayerStartPreferred(APlayerStart* SpawnPoint, AController* Player) const;

protected:

	virtual void SpawnLaneMinions();
	virtual void SpawnJungleMinions();
};
