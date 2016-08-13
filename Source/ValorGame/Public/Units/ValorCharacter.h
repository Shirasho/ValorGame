// Copyright Shirasho Media 2016. All rights reserved.

#pragma once

#include "ValorTypes.h"
#include "ValorClickableInterface.h"
#include "ValorHoverableInterface.h"
#include "ValorUnitInterface.h"
#include "ValorCharacter.generated.h"

DECLARE_STATS_GROUP(TEXT("ValorGame"), STATGROUP_ValorCharacter, STATCAT_Advanced);

UCLASS(Abstract)
class AValorCharacter : public ACharacter, public IValorUnitInterface, public IValorClickableInterface, public IValorHoverableInterface
{
	GENERATED_UCLASS_BODY()

protected:

	/* The hitbox used for registering ability hits on this character. */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"), Category = Character)
	UCapsuleComponent* AbilityHitbox;

	/* Default character stats that apply to all characters. */
	UPROPERTY(BlueprintReadOnly, Category = Stats)
	class UValorStatComponent* StatComponent;

	UPROPERTY(Replicated)
	bool bTargetable;

	UPROPERTY(Replicated)
	bool bDamageable;

	UPROPERTY(Replicated)
	bool bStealthed;

private:

	UPROPERTY(Replicated)
	EValorTeam CharacterTeam; // We want this hidden from inherited classes in order to force PlayerState refresh.

public:

	//virtual void PreInitializeComponents() override;

	//virtual void PostInitializeComponents() override;

	virtual void BeginPlay() override;

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

	UFUNCTION(BlueprintPure, Category = Stats)
	bool IsAlive() const;

	UFUNCTION(BlueprintPure, Category = Stats)
	EValorTeam GetTeam() const override;

	void SetTeam(EValorTeam NewTeam)
	{
		CharacterTeam = NewTeam;
	}

	UFUNCTION(BlueprintPure, Category = Stats)
	bool IsStealthed() const override
	{
		return bStealthed;
	}

	UFUNCTION(BlueprintPure, Category = Stats)
	bool IsDamageable() const
	{
		return bDamageable;
	}

	UFUNCTION(BlueprintPure, Category = Stats)
	bool IsTargetable() const
	{
		return bTargetable;
	}

public:

	UFUNCTION(BlueprintPure, Category = Stats)
	class UValorStatComponent* GetStatComponent() const;

public:

	/* Called when the player levels up. */
	virtual void OnLevelUp();

protected:

	virtual void Initialize(class APlayerState* InPlayerState = nullptr);

	UFUNCTION()
	virtual void OnMouseEnter(UPrimitiveComponent* TouchedComponent) override;
	UFUNCTION()
	virtual void OnMouseLeave(UPrimitiveComponent* TouchedComponent) override;
	UFUNCTION()
	virtual void OnMouseDown(UPrimitiveComponent* TouchedComponent, FKey ButtonPressed) override;
	UFUNCTION()
	virtual void OnMouseUp(UPrimitiveComponent* TouchedComponent, FKey ButtonPressed) override;
};