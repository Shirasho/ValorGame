// Copyright Shirasho Media 2016. All rights reserved.

#pragma once

#include "ValorTypes.h"
#include "ValorPlayerState.generated.h"

UCLASS()
class AValorPlayerState : public APlayerState
{
	GENERATED_UCLASS_BODY()

protected:

	UPROPERTY(Transient, ReplicatedUsing = OnRep_PlayerHero)
	TSubclassOf<class AValorHeroCharacter> HeroCharacter;

	UPROPERTY(Transient, ReplicatedUsing=OnRep_PlayerTeam)
	EValorTeam PlayerTeam;

	UPROPERTY(Transient, Replicated)
	uint32 PlayerKills;

	UPROPERTY(Transient, Replicated)
	uint32 PlayerDeaths;

	UPROPERTY(Transient, Replicated)
	uint32 PlayerAssists;

	UPROPERTY(Transient, ReplicatedUsing=OnRep_Inventory)
	TArray<AActor*> PlayerInventory;

	UPROPERTY()
	bool bLeaver;

protected:

	float PlayerInventory_HealthFromItems;
	float PlayerInventory_PrimaryResourceFromItems;

public:

	/** APLAYERSTATE INTERFACE */
	virtual void Reset() override;
	virtual void ClientInitialize(class AController* InController) override;
	virtual void UnregisterPlayerWithSession() override;
	virtual void CopyProperties(class APlayerState* PlayerState) override;

public:

	virtual bool IsEnemyOf(const AValorPlayerState* OtherPlayerState) const;

	float GetHealthFromItems() const;
	float GetPrimaryResourceFromItems() const;
	float GetHealthRegenFromItems(float BaseHealthRegen) const;
	float GetPrimaryResourceRegenFromItems(float BasePrimaryResourceRegen) const;

public:

	void SetTeam(EValorTeam NewTeam);

	void ScoreKill(AValorPlayerState* Victim);

	void ScoreDeath(AValorPlayerState* KilledBy);

	void ScoreAssist(AValorPlayerState* Victim);

	void SetLeaver(bool bInLeaver);

	EValorTeam GetTeam() const;
	uint32 GetKills() const;
	uint32 GetDeaths() const;
	uint32 GetAssists() const;
	bool IsLeaver() const;

	FString GetShortPlayerName() const;

protected:

	UFUNCTION()
	virtual void OnRep_PlayerTeam();

	UFUNCTION()
	virtual void OnRep_Inventory();

	UFUNCTION()
	virtual void OnRep_PlayerHero();
};