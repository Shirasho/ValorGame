// Copyright Shirasho Media 2016. All rights reserved.

#pragma once

#include "Components/ActorComponent.h"
#include "ValorDataDefinitions.h"
#include "ValorCharacterStatTableRow.h"
#include "ValorCharacterExperienceTableRow.h"
#include "ValorStatComponent.generated.h"


UCLASS(ClassGroup=Valor, meta=(BlueprintSpawnableComponent))
class VALORGAME_API UValorStatComponent : public UActorComponent
{
	GENERATED_BODY()

public:	

	UValorStatComponent();

	virtual void BeginPlay() override;
	
	virtual void TickComponent( float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction ) override;

private:

	void RecoverStats();

public:

	UFUNCTION(BlueprintPure, Category = Stats)
		virtual float GetMaxHealth() const;

	UFUNCTION(BlueprintPure, Category = Stats)
		virtual float GetMaxPrimaryResource() const;

	UFUNCTION(BlueprintPure, Category = Stats)
		virtual float GetMaxSecondaryResource() const;

	UFUNCTION(BlueprintPure, Category = Stats)
		virtual float GetHealth() const;

	UFUNCTION(BlueprintPure, Category = Stats)
		virtual float GetBaseHealth() const;

	UFUNCTION(BlueprintPure, Category = Stats)
		virtual float GetBonusHealth() const;

	UFUNCTION(BlueprintPure, Category = Stats)
		virtual float GetHealthRegen() const;

	UFUNCTION(BlueprintPure, Category = Stats)
		virtual float GetBaseHealthRegen() const;

	UFUNCTION(BlueprintPure, Category = Stats)
		virtual float GetBonusHealthRegen() const;

	UFUNCTION(BlueprintPure, Category = Stats)
		virtual float GetPrimaryResource() const;

	UFUNCTION(BlueprintPure, Category = Stats)
		virtual float GetBasePrimaryResource() const;

	UFUNCTION(BlueprintPure, Category = Stats)
		virtual float GetBonusPrimaryResource() const;

	UFUNCTION(BlueprintPure, Category = Stats)
		virtual float GetPrimaryResourceRegen() const;

	UFUNCTION(BlueprintPure, Category = Stats)
		virtual float GetBasePrimaryResourceRegen() const;

	UFUNCTION(BlueprintPure, Category = Stats)
		virtual float GetBonusPrimaryResourceRegen() const;

	UFUNCTION(BlueprintPure, Category = Stats)
		virtual float GetSecondaryResource() const;

	UFUNCTION(BlueprintPure, Category = Stats)
		virtual float GetBaseSecondaryResource() const;

	UFUNCTION(BlueprintPure, Category = Stats)
		virtual float GetBonusSecondaryResource() const;

	UFUNCTION(BlueprintPure, Category = Stats)
		virtual float GetSecondaryResourceRegen() const;

	UFUNCTION(BlueprintPure, Category = Stats)
		virtual float GetBaseSecondaryResourceRegen() const;

	UFUNCTION(BlueprintPure, Category = Stats)
		virtual float GetBonusSecondaryResourceRegen() const;

public:

		void IncrementLevel();

		void OnItemPurchased();

	UFUNCTION(BlueprintCallable, Category = Stats)
		void AdjustHealth(float Amount);

	UFUNCTION(BlueprintCallable, Category = Stats)
		void AdjustPrimaryResource(float Amount);

	UFUNCTION(BlueprintCallable, Category = Stats)
		void AdjustSecondaryResource(float Amount);

	UFUNCTION(BlueprintCallable, Category = Stats)
		void AdjustHealthRegen(float Amount);

	UFUNCTION(BlueprintCallable, Category = Stats)
		void AdjustPrimaryResourceRegen(float Amount);

	UFUNCTION(BlueprintCallable, Category = Stats)
		void AdjustSecondaryResourceRegen(float Amount);

public:

	UFUNCTION(BlueprintCallable, Category = Stats)
		void RecalculateStats(const bool bOnInit, const bool bOnLevelUp);

protected:

	UFUNCTION(BlueprintNativeEvent, Category = "Stats|Replication")
		void OnRep_Health();
	UFUNCTION(BlueprintNativeEvent, Category = "Stats|Replication")
		void OnRep_PrimaryResource();
	UFUNCTION(BlueprintNativeEvent, Category = "Stats|Replication")
		void OnRep_SecondaryResource();
	UFUNCTION(BlueprintNativeEvent, Category = "Stats|Replication")
		void OnRep_HealthRegen();
	UFUNCTION(BlueprintNativeEvent, Category = "Stats|Replication")
		void OnRep_PrimaryResourceRegen();
	UFUNCTION(BlueprintNativeEvent, Category = "Stats|Replication")
		void OnRep_SecondaryResourceRegen();

	UFUNCTION(BlueprintNativeEvent, Category = "Stats|Replication")
		void OnRep_BonusHealth();
	UFUNCTION(BlueprintNativeEvent, Category = "Stats|Replication")
		void OnRep_BonusPrimaryResource();
	UFUNCTION(BlueprintNativeEvent, Category = "Stats|Replication")
		void OnRep_BonusSecondaryResource();
	UFUNCTION(BlueprintNativeEvent, Category = "Stats|Replication")
		void OnRep_BonusHealthRegen();
	UFUNCTION(BlueprintNativeEvent, Category = "Stats|Replication")
		void OnRep_BonusPrimaryResourceRegen();
	UFUNCTION(BlueprintNativeEvent, Category = "Stats|Replication")
		void OnRep_BonusSecondaryResourceRegen();

private:

	void SetBaseStats();
	void SetBaseExperience();

	void SetBonusHealth(const class AValorPlayerState* PlayerState);
	void SetBonusPrimaryResource(const class AValorPlayerState* PlayerState);
	void SetBonusSecondaryResource(const class AValorPlayerState* PlayerState);
	void SetBonusHealthRegen(const class AValorPlayerState* PlayerState);
	void SetBonusPrimaryResourceRegen(const class AValorPlayerState* PlayerState);
	void SetBonusSecondaryResourceRegen(const class AValorPlayerState* PlayerState);

	void SetHealth(const class AValorPlayerState* PlayerState, const bool bOnInit, const bool bOnLevelUp);
	void SetPrimaryResource(const class AValorPlayerState* PlayerState, const bool bOnInit, const bool bOnLevelUp);
	void SetSecondaryResource(const class AValorPlayerState* PlayerState, const bool bOnInit, const bool bOnLevelUp);

public:

	UPROPERTY(EditDefaultsOnly, Category = General)
		bool bRequiresStatInformation;

	/* The external data table to read the base stats from. */
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, meta = (EditCondition = bRequiresStatInformation), Category = General)
		FDataTableRowHandle StatInformation;
	/* The external data table to read the experience from. */
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = General)
		FDataTableRowHandle ExperienceInformation;

	/* The number of times to recover the stats every 5 seconds. For example, a value of '20' will
	 * cause a tick every .25 seconds. */
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = General)
		uint8 RecoverTickFrequency;

protected:

	/* The current level of the character. */
	UPROPERTY(BlueprintReadOnly, Transient, Replicated, Category = Stats)
		uint8 Level;
	/* The current health of the character. */
	UPROPERTY(BlueprintReadOnly, Transient, ReplicatedUsing=OnRep_Health, Category = Stats)
		float Health;
	/* The current health of the character. */
	UPROPERTY(BlueprintReadOnly, Transient, Replicated, Category = Stats)
		int32 Experience;
	/* The current primary resource (mana) of the character. */
	UPROPERTY(BlueprintReadOnly, ReplicatedUsing=OnRep_PrimaryResource, Category = Stats)
		float PrimaryResource;
	/* The current secondary resource (character-specific) of the character. */
	UPROPERTY(BlueprintReadOnly, ReplicatedUsing=OnRep_SecondaryResource, Category = Stats)
		float SecondaryResource;
	/* The current health regen of the character. */
	UPROPERTY(BlueprintReadOnly, ReplicatedUsing=OnRep_HealthRegen, Category = Stats)
		float HealthRegen;
	/* The current health regen of the character. */
	UPROPERTY(BlueprintReadOnly, ReplicatedUsing=OnRep_PrimaryResourceRegen, Category = Stats)
		float PrimaryResourceRegen;
	/* The current health regen of the character. */
	UPROPERTY(BlueprintReadOnly, ReplicatedUsing=OnRep_SecondaryResourceRegen, Category = Stats)
		float SecondaryResourceRegen;

protected:

	UPROPERTY(BlueprintReadOnly, ReplicatedUsing=OnRep_BonusHealth, Category = Stats)
		float BonusHealth;

	UPROPERTY(BlueprintReadOnly, ReplicatedUsing = OnRep_BonusPrimaryResource, Category = Stats)
		float BonusPrimaryResource;

	UPROPERTY(BlueprintReadOnly, ReplicatedUsing = OnRep_BonusSecondaryResource, Category = Stats)
		float BonusSecondaryResource;

	UPROPERTY(BlueprintReadOnly, ReplicatedUsing = OnRep_BonusHealthRegen, Category = Stats)
		float BonusHealthRegen;

	UPROPERTY(BlueprintReadOnly, ReplicatedUsing = OnRep_BonusPrimaryResourceRegen, Category = Stats)
		float BonusPrimaryResourceRegen;

	UPROPERTY(BlueprintReadOnly, ReplicatedUsing = OnRep_BonusSecondaryResourceRegen, Category = Stats)
		float BonusSecondaryResourceRegen;

public:

	UPROPERTY(BlueprintReadOnly, Category = Stats)
		TArray<int32> ExperienceRequiredPerLevel;

	UPROPERTY(BlueprintReadOnly, Category = Stats)
		TArray<float> BaseHealthPerLevel;

	UPROPERTY(BlueprintReadOnly, Category = Stats)
		TArray<float> BasePrimaryResourcePerLevel;

	UPROPERTY(BlueprintReadOnly, Category = Stats)
		TArray<float> BaseSecondaryResourcePerLevel;

	UPROPERTY(BlueprintReadOnly, Category = Stats)
		TArray<float> BaseHealthRegenPerLevel;

	UPROPERTY(BlueprintReadOnly, Category = Stats)
		TArray<float> BasePrimaryResourceRegenPerLevel;

	UPROPERTY(BlueprintReadOnly, Category = Stats)
		TArray<float> BaseSecondaryResourceRegenPerLevel;

private:

	FTimerHandle TimerHandle_RecoverStats;

	bool bSetupComplete;
};
