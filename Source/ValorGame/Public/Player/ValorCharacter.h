// Copyright Shirasho Media 2016. All rights reserved.

#pragma once

#include "ValorTypes.h"
#include "ValorCharacterStatTableRow.h"
#include "ValorCharacter.generated.h"

class UValorCharacterMovementComponent;

UCLASS(Abstract)
class AValorCharacter : public ACharacter
{
	GENERATED_UCLASS_BODY()

protected:

	/* The number of times that RecoverStats() should be called within the full duration specified by GetStatRecoveryFrequencyTime(). */
	virtual float GetStatRecoveryFrequency() const
	{
		// We want to update every 1.25 seconds.
		return 4;
	}
	/* The number of seconds of the full duration (i.e. 10 regen per X seconds) where X is the returned value. */
	virtual float GetStatRecoveryFrequencyTime() const
	{
		// We want our recovery in units of "per 5 seconds".
		return 5;
	}

protected:

	/* The hitbox used for registering ability hits on this character. */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"), Category = Character)
	UCapsuleComponent* AbilityHitbox;

	/* The hitbox used for collision with other characters. */
	/*UPROPERTY(Category = Character, EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
	UCapsuleComponent* CharacterHitbox;*/

	/* The hitbox used for collision with terrain. */
	/*UPROPERTY(Category = Character, EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
	UCapsuleComponent* TerrainHitbox;*/

protected:

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = Stats)
	FDataTableRowHandle StatInformation;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Stats)
	float BaseHealth;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Stats)
	float BaseHealthRegen;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Stats)
	float BasePrimaryResource;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Stats)
	float BasePrimaryResourceRegen;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Stats)
	float BaseSecondaryResource;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Stats)
	float BaseSecondaryResourceRegen;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Stats)
	float MaxSecondaryResource;


	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Stats)
	float BonusHealthFromLevel;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Stats)
	float BonusPrimaryResourceFromLevel;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Stats)
	float BonusHealthRegenFromLevel;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Stats)
	float BonusPrimaryResourceRegenFromLevel;


	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Replicated, Category = Stats)
	float Health;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Replicated, Category = Stats)
	float PrimaryResource;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Replicated, Category = Stats)
	float SecondaryResource;

private:

	FTimerHandle TimerHandle_StatRecovery;

	//UPROPERTY(VisibleAnywhere, BlueprintReadable, meta = (AllowPrivateAccess = "true"), Category = Stats)

public:

	virtual void PostInitializeComponents() override;

	virtual void Tick(float DeltaSeconds) override;

public:

	/* [Server] Returns whether the specified character is an enemy of this character. */
	UFUNCTION(BlueprintPure, Category = Stats)
	virtual bool IsEnemyOf(const AValorCharacter* OtherCharacter) const;

	/* Play the specified animation montage. Note that heros are only valid on the server. */
	virtual float PlayAnimMontage(class UAnimMontage* AnimMontage, float InPlayRate = 1.f, FName StartSectionName = NAME_None) override;

	/* Stop the specified montage. Note that heros are only valid on the server. */
	virtual void StopAnimMontage(class UAnimMontage* AnimMontage) override;

	/* Stop playing all montages. Note that heros are only valid on the server. */
	void StopAllAnimMontages();

public:

	UFUNCTION(BlueprintPure, Category = Stats)
	bool IsAlive() const;

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
		virtual float GetHealthRegen() const;

	UFUNCTION(BlueprintPure, Category = Stats)
		virtual float GetBaseHealthRegen() const;


	UFUNCTION(BlueprintPure, Category = Stats)
		virtual float GetPrimaryResource() const;

	UFUNCTION(BlueprintPure, Category = Stats)
		virtual float GetBasePrimaryResource() const;

	UFUNCTION(BlueprintPure, Category = Stats)
		virtual float GetPrimaryResourceRegen() const;

	UFUNCTION(BlueprintPure, Category = Stats)
		virtual float GetBasePrimaryResourceRegen() const;


	UFUNCTION(BlueprintPure, Category = Stats)
		virtual float GetSecondaryResource() const;

	UFUNCTION(BlueprintPure, Category = Stats)
		virtual float GetBaseSecondaryResource() const;

	UFUNCTION(BlueprintPure, Category = Stats)
		virtual float GetSecondaryResourceRegen() const;

	UFUNCTION(BlueprintPure, Category = Stats)
		virtual float GetBaseSecondaryResourceRegen() const;

	EValorTeam GetTeam() const;

protected:

	/* Called when it is time to recover the character's stats. */
	virtual void RecoverStats();

	/* Called when the player levels up. */
	virtual void OnLevelUp();
};