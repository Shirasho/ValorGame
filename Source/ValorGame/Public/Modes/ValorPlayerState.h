// Copyright Shirasho Media 2016. All rights reserved.

#pragma once

#include "ValorTypes.h"
#include "ValorInventoryItem.h"
#include "ValorPlayerState.generated.h"

UCLASS()
class AValorPlayerState : public APlayerState
{
	GENERATED_UCLASS_BODY()

public:

	UPROPERTY(Transient, ReplicatedUsing = OnRep_PlayerHero)
	TSubclassOf<class AValorHeroCharacter> HeroCharacter;

protected:

	UPROPERTY(Transient, ReplicatedUsing=OnRep_PlayerTeam)
	EValorTeam PlayerTeam;

	UPROPERTY(Transient, Replicated)
	uint32 PlayerKills;

	UPROPERTY(Transient, Replicated)
	uint32 PlayerDeaths;

	UPROPERTY(Transient, Replicated)
	uint32 PlayerAssists;

	UPROPERTY(Transient, Replicated)
	uint8 PlayerLevel;

	UPROPERTY(Transient, Replicated)
	int32 PlayerExperience;

	UPROPERTY(Transient, ReplicatedUsing=OnRep_Inventory)
	TArray<FValorInventoryItem> PlayerInventory;

	UPROPERTY()
	bool bLeaver;

public:

	/** APLAYERSTATE INTERFACE */
	virtual void Reset() override;
	virtual void ClientInitialize(class AController* InController) override;
	virtual void UnregisterPlayerWithSession() override;
	virtual void CopyProperties(class APlayerState* PlayerState) override;

public:

	virtual bool IsEnemyOf(const AValorPlayerState* OtherPlayerState) const;

public:

	void IncrementPlayerLevel(const TArray<int32>& ExperienceRequiredToLevel);

public:

	void SetTeam(EValorTeam NewTeam);

	void ScoreKill(AValorPlayerState* Victim);

	void ScoreDeath(AValorPlayerState* KilledBy);

	void ScoreAssist(AValorPlayerState* Victim);

	void SetLeaver(bool bInLeaver);

	EValorTeam GetPlayerTeam() const;
	uint32 GetPlayerKills() const;
	uint32 GetPlayerDeaths() const;
	uint32 GetPlayerAssists() const;
	uint8 GetPlayerLevel() const;
	int32 GetPlayerExperience() const;

	bool IsLeaver() const;

	const TArray<FValorInventoryItem>& GetPlayerInventory() const;

	float GetPlayerHealthFromItems(const float BaseHealth, const float BonusHealth) const;
	float GetPlayerPrimaryResourceFromItems(const float BasePrimaryResource, const float BonusPrimaryResource) const;
	float GetPlayerSecondaryResourceFromItems(const float BaseSecondaryResource, const float BonusSecondaryResource) const;
	
	float GetPlayerHealthRegenFromItems(const float BaseHealthRegen, const float BonusHealthRegen, const float BaseHealth, const float BonusHealth) const;
	float GetPlayerPrimaryResourceRegenFromItems(const float BasePrimaryResourceRegen, const float BonusPrimaryResourceRegen, const float BasePrimaryResource, const float BonusPrimaryResource) const;
	float GetPlayerSecondaryResourceRegenFromItems(const float BaseSecondaryResourceRegen, const float BonusSecondaryResourceRegen, const float BaseSecondaryResource, const float BonusSecondaryResource) const;

	FString GetShortPlayerName() const;

protected:

	UFUNCTION()
	virtual void OnRep_PlayerTeam();

	UFUNCTION()
	virtual void OnRep_Inventory();

	UFUNCTION()
	virtual void OnRep_PlayerHero();
};