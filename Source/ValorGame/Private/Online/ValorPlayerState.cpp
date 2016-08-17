// Copyright Shirasho Media 2016. All rights reserved.

#include "ValorGame.h"
#include "ValorPlayerState.h"

#include "ValorGameMode.h"
#include "ValorPlayerDefinitions.h"
#include "ValorHeroCharacter.h"

AValorPlayerState::AValorPlayerState(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer)
{
	PlayerTeam = EValorTeam::One;
	PlayerKills = 0;
	PlayerDeaths = 0;
	PlayerAssists = 0;
	PlayerLevel = 1;
	PlayerExperience = 0;
	bLeaver = false;

	if (HasAuthority())
	{
		static ConstructorHelpers::FClassFinder<AValorHeroCharacter> CH_PlayerPawn(TEXT("/Game/Units/Heros/Natsu/Natsu_BP"));
		if (CH_PlayerPawn.Succeeded())
		{
			HeroCharacter = CH_PlayerPawn.Class;
		}
	}
}

void AValorPlayerState::Reset()
{
	Super::Reset();

	PlayerTeam = EValorTeam::None;
	PlayerKills = 0;
	PlayerDeaths = 0;
	PlayerAssists = 0;
	PlayerLevel = 1;
	PlayerExperience = 0;
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
	check(NewTeam != EValorTeam::Invalid);
	PlayerTeam = NewTeam;
}

void AValorPlayerState::OnRep_PlayerTeam()
{

}

void AValorPlayerState::OnRep_Inventory()
{

}

void AValorPlayerState::OnRep_PlayerHero()
{

}

void AValorPlayerState::AdjustExperience(int32 Value)
{
	PlayerExperience = FMath::Max(PlayerExperience + Value, 0);
}

uint8 AValorPlayerState::IncrementPlayerLevel(const TArray<int32>& ExperienceRequiredToLevel)
{
	if (HasAuthority())
	{
		const AValorGameMode* GameMode = GetWorld()->GetAuthGameMode<AValorGameMode>();

		// Must be true for server.
		check(GameMode);

		uint8 MaxPlayerLevel = GameMode->GetMaximumLevel();

		uint8 GainedLevels = 0;

		while (PlayerLevel < MaxPlayerLevel && ExperienceRequiredToLevel.IsValidIndex(PlayerLevel-1) && PlayerExperience >= ExperienceRequiredToLevel[PlayerLevel - 1])
		{
			PlayerExperience = FMath::Max(PlayerExperience - FMath::Abs(ExperienceRequiredToLevel[PlayerLevel - 1]), 0);
			++PlayerLevel;
			++GainedLevels;
		}

		return GainedLevels;
	}

	return 0;
}

EValorTeam AValorPlayerState::GetPlayerTeam() const
{
	check(PlayerTeam != EValorTeam::Invalid);
	return PlayerTeam;
}

uint8 AValorPlayerState::GetPlayerLevel() const
{
	return PlayerLevel;
}

int32 AValorPlayerState::GetPlayerExperience() const
{
	return PlayerExperience;
}

bool AValorPlayerState::IsLeaver() const
{
	return bLeaver;
}

uint32 AValorPlayerState::GetPlayerKills() const
{
	return PlayerKills;
}

uint32 AValorPlayerState::GetPlayerDeaths() const
{
	return PlayerDeaths;
}

uint32 AValorPlayerState::GetPlayerAssists() const
{
	return PlayerAssists;
}

const TArray<FValorInventoryItem>& AValorPlayerState::GetPlayerInventory() const
{
	return PlayerInventory;
}

float AValorPlayerState::GetPlayerHealthFromItems(const float BaseHealth, const float BonusHealth) const
{
	return 0.f;
}

float AValorPlayerState::GetPlayerPrimaryResourceFromItems(const float BasePrimaryResource, const float BonusPrimaryResource) const
{
	return 0.f;
}

float AValorPlayerState::GetPlayerSecondaryResourceFromItems(const float BaseSecondaryResource, const float BonusSecondaryResource) const
{
	return 0.f;
}

float AValorPlayerState::GetPlayerHealthRegenFromItems(const float BaseHealthRegen, const float BonusHealthRegen, const float BaseHealth, const float BonusHealth) const
{
	return 0.f;
}
float AValorPlayerState::GetPlayerPrimaryResourceRegenFromItems(const float BasePrimaryResourceRegen, const float BonusPrimaryResourceRegen, const float BasePrimaryResource, const float BonusPrimaryResource) const
{
	return 0.f;
}
float AValorPlayerState::GetPlayerSecondaryResourceRegenFromItems(const float BaseSecondaryResourceRegen, const float BonusSecondaryResourceRegen, const float BaseSecondaryResource, const float BonusSecondaryResource) const
{
	return 0.f;
}

FString AValorPlayerState::GetShortPlayerName() const
{
	if (PlayerName.Len() > VALOR_PLAYER_MAX_NAME_LENGTH)
	{
		return PlayerName.Left(VALOR_PLAYER_MAX_NAME_LENGTH) + TEXT("...");
	}

	return PlayerName;
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
	}
}

void AValorPlayerState::GetLifetimeReplicatedProps(TArray< FLifetimeProperty > & OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);

	DOREPLIFETIME(AValorPlayerState, PlayerTeam);
	DOREPLIFETIME(AValorPlayerState, PlayerKills);
	DOREPLIFETIME(AValorPlayerState, PlayerDeaths);
	DOREPLIFETIME(AValorPlayerState, PlayerAssists);
	DOREPLIFETIME(AValorPlayerState, PlayerLevel);
	DOREPLIFETIME(AValorPlayerState, PlayerExperience);
	DOREPLIFETIME(AValorPlayerState, PlayerInventory);
}