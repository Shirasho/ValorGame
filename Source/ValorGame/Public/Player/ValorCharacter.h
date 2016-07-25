// Copyright Shirasho Media 2016. All rights reserved.

#pragma once

#include "ValorTypes.h"
#include "ValorCharacterStatContainer.h"
#include "ValorCharacter.generated.h"

#define VALOR_MAX_CHARACTER_LEVEL 20

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

private:

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Replicated, meta=(AllowPrivateAccess="true"), Category = Stats)
	FValorCharacterStatContainer CharacterStats;

private:

	FTimerHandle TimerHandle_StatRecovery;

public:

	virtual void PossessedBy(AController* Controller) override;

	virtual void PostInitializeComponents() override;

	virtual void BeginPlay() override;

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
	EValorTeam GetTeam() const;

protected:

	UFUNCTION(BlueprintPure, Category = Stats)
	const FValorCharacterStatContainer& GetCharacterStats() const;

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
	
	UFUNCTION(BlueprintCallable, Category = Stats)
		void IncrementLevel();
	
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

	/* Called when the player levels up. */
	virtual void OnLevelUp();

protected:

	/* Called when it is time to recover the character's stats. */
	virtual void RecoverStats();

	virtual void RecalculateNonResourceStats();
};