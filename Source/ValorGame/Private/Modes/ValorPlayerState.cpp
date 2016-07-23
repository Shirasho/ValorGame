// Copyright Shirasho Media 2016. All rights reserved.

#include "ValorGame.h"
#include "ValorPlayerState.h"

#include "ValorPlayerDefinitions.h"

#include "ValorHeroCharacter.h"

AValorPlayerState::AValorPlayerState(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer)
{
	PlayerTeam = EValorTeam::None;
	PlayerKills = 0;
	PlayerDeaths = 0;
	PlayerAssists = 0;
	PlayerInventory_HealthFromItems = 0;
	PlayerInventory_PrimaryResourceFromItems = 0;
	bLeaver = false;
}

void AValorPlayerState::Reset()
{
	Super::Reset();

	PlayerTeam = EValorTeam::None;
	PlayerKills = 0;
	PlayerDeaths = 0;
	PlayerAssists = 0;
	PlayerInventory_HealthFromItems = 0;
	PlayerInventory_PrimaryResourceFromItems = 0;
	bLeaver = false;
}

void AValorPlayerState::ClientInitialize(AController* InController)
{
	Super::ClientInitialize(InController);
}

bool AValorPlayerState::IsEnemyOf(const AValorPlayerState* Other) const
{
	return (PlayerTeam == EValorTeam::None) || (PlayerTeam != Other->PlayerTeam);
}

void AValorPlayerState::SetLeaver(bool bInLeaver)
{
	bLeaver = bInLeaver;
}

void AValorPlayerState::SetTeam(EValorTeam NewTeam)
{
	PlayerTeam = NewTeam;
}

void AValorPlayerState::OnRep_PlayerTeam()
{

}

void AValorPlayerState::OnRep_Inventory()
{
	PlayerInventory_HealthFromItems = 0;
	PlayerInventory_PrimaryResourceFromItems = 0;

	for (const AActor* InventoryItem : PlayerInventory)
	{
		PlayerInventory_HealthFromItems += 0;
		PlayerInventory_PrimaryResourceFromItems += 0;
	}
}

void AValorPlayerState::OnRep_PlayerHero()
{

}

EValorTeam AValorPlayerState::GetTeam() const
{
	return PlayerTeam;
}

bool AValorPlayerState::IsLeaver() const
{
	return bLeaver;
}

uint32 AValorPlayerState::GetKills() const
{
	return PlayerKills;
}

uint32 AValorPlayerState::GetDeaths() const
{
	return PlayerDeaths;
}

uint32 AValorPlayerState::GetAssists() const
{
	return PlayerAssists;
}

FString AValorPlayerState::GetShortPlayerName() const
{
	if (PlayerName.Len() > VALOR_PLAYER_MAX_NAME_LENGTH)
	{
		return PlayerName.Left(VALOR_PLAYER_MAX_NAME_LENGTH) + TEXT("...");
	}

	return PlayerName;
}

float AValorPlayerState::GetHealthFromItems() const
{
	return PlayerInventory_HealthFromItems;
}

float AValorPlayerState::GetPrimaryResourceFromItems() const
{
	return PlayerInventory_PrimaryResourceFromItems;
}

float AValorPlayerState::GetHealthRegenFromItems(float BaseHealthRegen) const
{
	/* We need to iterate over the inventory for this one. */
	return 0.f;
}

float AValorPlayerState::GetPrimaryResourceRegenFromItems(float BasePrimaryResourceRegen) const
{
	/* We need to iterate over the inventory for this one. */
	return 0.f;
}

void AValorPlayerState::ScoreKill(AValorPlayerState* Victim)
{
	++PlayerKills;
}

void AValorPlayerState::ScoreDeath(AValorPlayerState* KilledBy)
{
	++PlayerDeaths;
}

void AValorPlayerState::ScoreAssist(AValorPlayerState* Victim)
{
	++PlayerAssists;
}

void AValorPlayerState::UnregisterPlayerWithSession()
{
	if (!bFromPreviousLevel)
	{
		Super::UnregisterPlayerWithSession();
	}
}

void AValorPlayerState::CopyProperties(APlayerState* PlayerState)
{
	Super::CopyProperties(PlayerState);

	AValorPlayerState* ValorPlayerState = Cast<AValorPlayerState>(PlayerState);
	if (ValorPlayerState)
	{
		ValorPlayerState->HeroCharacter = HeroCharacter;


		/*ValorPlayerState->PlayerKills = PlayerKills;
		ValorPlayerState->PlayerDeaths = PlayerDeaths;
		ValorPlayerState->PlayerAssists = PlayerAssists;
		ValorPlayerState->PlayerTeam = PlayerTeam;
		ValorPlayerState->PlayerInventory = PlayerInventory;*/
	}
}

void AValorPlayerState::GetLifetimeReplicatedProps(TArray< FLifetimeProperty > & OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);

	DOREPLIFETIME(AValorPlayerState, PlayerTeam);
	DOREPLIFETIME(AValorPlayerState, PlayerKills);
	DOREPLIFETIME(AValorPlayerState, PlayerDeaths);
	DOREPLIFETIME(AValorPlayerState, PlayerAssists);
	DOREPLIFETIME(AValorPlayerState, PlayerInventory);
}