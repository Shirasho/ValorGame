// Copyright Shirasho Media 2016. All rights reserved.

#pragma once

#include "ValorTypes.h"
#include "ValorCharacter.generated.h"

UCLASS(Abstract)
class AValorCharacter : public ACharacter
{
	GENERATED_UCLASS_BODY()

protected:

	/* The hitbox used for registering ability hits on this character. */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"), Category = Character)
	UCapsuleComponent* AbilityHitbox;

	/* Default character stats that apply to all characters. */
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	class UValorStatComponent* StatComponent;

	UPROPERTY(Replicated)
	bool bTargetable;

	UPROPERTY(Replicated)
	bool bDamageable;

private:

	UPROPERTY(Replicated)
	EValorTeam CharacterTeam; // We want this hidden from BP in order to force PlayerState refresh.

public:

	//virtual void PreInitializeComponents() override;

	//virtual void PostInitializeComponents() override;

	//virtual void BeginPlay() override;

	//virtual void EndPlay(const EEndPlayReason::Type EndPlayReason) override;

	//virtual void Tick(float DeltaSeconds) override;

	//virtual void PossessedBy(AController* Controller) override;

	virtual float TakeDamage(float DamageAmount, FDamageEvent const& DamageEvent, AController* EventInstigator, AActor* DamageCauser) override;

public:

	/* [Client, Unreliable, NoDedicatedServer] React to damage (such as updating the UI, playing sounds, and activating animations and particles. */
	UFUNCTION(BlueprintNativeEvent, Category = Damage)
		void OnDamageTaken(float DamageAmount, bool bKilledUnit, UPARAM(ref) FDamageEvent const& DamageEvent, AActor* DamageCauser);

	UFUNCTION(Client, Reliable, Category = Damage)
		void ClientOnDamageTaken(float DamageAmount, bool bKilledUnit, FDamageEvent const& DamageEvent, AActor* DamageCauser);

	UFUNCTION(NetMulticast, Unreliable, Category = Damage)
		void MulticastOnDamageTaken(float DamageAmount, bool bKilledUnit, FDamageEvent const& DamageEvent, AActor* DamageCauser);

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

	void InitStats();

	UFUNCTION(BlueprintPure, Category = Stats)
	bool IsAlive() const;

	UFUNCTION(BlueprintPure, Category = Stats)
	EValorTeam GetTeam() const;

	void SetTeam(EValorTeam NewTeam)
	{
		CharacterTeam = NewTeam;
	}

public:

	UFUNCTION(BlueprintPure, Category = Stats)
	class UValorStatComponent* GetStatComponent() const;

public:
	
	UFUNCTION(BlueprintCallable, Category = Stats)
	void IncrementLevel();

	/* Called when the player levels up. */
	virtual void OnLevelUp();
};