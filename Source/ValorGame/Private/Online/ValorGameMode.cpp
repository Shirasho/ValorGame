// Copyright Shirasho Media 2016. All rights reserved.

#include "ValorGame.h"
#include "ValorGameMode.h"

#include "ValorHUD.h"
#include "ValorPlayerController.h"
#include "ValorPlayerState.h"
#include "ValorSpectatorPawn.h"
#include "ValorGameState.h"
#include "ValorGameSession.h"
#include "ValorDemoSpectator.h"

#include "ValorPlayerStart.h"
#include "ValorLaneSpawner.h"
#include "ValorJungleSpawner.h"

#include "ValorHeroController.h"
#include "ValorHeroCharacter.h"

#include "ValorHeroCharacterProxy.h"


AValorGameMode::AValorGameMode(const FObjectInitializer& ObjectInitializer) 
	: Super(ObjectInitializer)
{
	DefaultPawnClass = AValorHeroCharacterProxy::StaticClass();
	PlayerControllerClass = AValorPlayerController::StaticClass();

	HUDClass = AValorHUD::StaticClass();
	PlayerStateClass = AValorPlayerState::StaticClass();
	SpectatorClass = AValorSpectatorPawn::StaticClass();
	GameStateClass = AValorGameState::StaticClass();
	ReplaySpectatorPlayerControllerClass = AValorDemoSpectator::StaticClass();

	bUseSeamlessTravel = true;
}

TSubclassOf<AGameSession> AValorGameMode::GetGameSessionClass() const
{
	return AValorGameSession::StaticClass();
}

bool AValorGameMode::AllowCheats(APlayerController* P)
{
	return true;
}

AActor* AValorGameMode::ChoosePlayerStart_Implementation(AController* Player)
{
	TArray<APlayerStart*> PreferredSpawns;
	TArray<APlayerStart*> FallbackSpawns;

	APlayerStart* BestStart = nullptr;

	// Always prefer the first "Play from Here" PlayerStart, if we find one while in PIE mode.
	for (TActorIterator<APlayerStart> It(GetWorld()); It; ++It)
	{
		APlayerStart* TestSpawn = *It;
		if (TestSpawn->IsA<APlayerStartPIE>())
		{
			return TestSpawn;
		}
	}

	/* NOTE - objects can only be spawned into the persistent level. Using TObjectIterator would
	 * fix the issue, but we run into potential PIE object conflicts. */
	for (TActorIterator<AValorPlayerStart> It(Player->GetWorld()); It; ++It)
	//for (TObjectIterator<AValorPlayerStart> It; It; ++It)
	{
		AValorPlayerStart* TestSpawn = *It;

		if (IsPlayerStartAllowed(TestSpawn, Player))
		{
			if (IsPlayerStartPreferred(TestSpawn, Player))
			{
				PreferredSpawns.Add(TestSpawn);
			}
			else
			{
				FallbackSpawns.Add(TestSpawn);
			}
		}
	}

	if (PreferredSpawns.Num() > 0)
	{
		BestStart = PreferredSpawns[FMath::RandHelper(PreferredSpawns.Num())];
	}
	else if (FallbackSpawns.Num() > 0)
	{
		BestStart = FallbackSpawns[FMath::RandHelper(FallbackSpawns.Num())];
	}
	

	return BestStart ? BestStart : Super::ChoosePlayerStart_Implementation(Player);
}

UClass* AValorGameMode::GetDefaultPawnClassForController_Implementation(AController* InController)
{
	return Super::GetDefaultPawnClassForController_Implementation(InController);
}

bool AValorGameMode::IsPlayerStartAllowed(APlayerStart* SpawnPoint, AController* Player) const
{
	const AValorPlayerStart* ValorPlayerStart = Cast<AValorPlayerStart>(SpawnPoint);
	if (ValorPlayerStart)
	{
		const AValorHeroController* ValorHeroController = Cast<AValorHeroController>(Player);

		if (!ValorHeroController)
		{
			return false;
		}

		return ((static_cast<uint8>(ValorHeroController->GetValorHeroCharacter()->GetTeam()) & ValorPlayerStart->SpawnTeam) > 0);
	}

	return false;
}

bool AValorGameMode::IsPlayerStartPreferred(APlayerStart* SpawnPoint, AController* Player) const
{
	ACharacter* MyPawn = Cast<ACharacter>((*DefaultPawnClass)->GetDefaultObject<ACharacter>());
	AValorHeroController* ValorHeroController = Cast<AValorHeroController>(Player);
	if (ValorHeroController)
	{
		MyPawn = Cast<ACharacter>(AValorHeroCharacter::StaticClass()->GetDefaultObject<ACharacter>());
	}

	if (MyPawn)
	{
		const FVector SpawnLocation = SpawnPoint->GetActorLocation();
		for (FConstPawnIterator It = GetWorld()->GetPawnIterator(); It; ++It)
		{
			ACharacter* OtherPawn = Cast<ACharacter>(*It);
			if (OtherPawn && OtherPawn != MyPawn)
			{
				const float CombinedHeight = (MyPawn->GetCapsuleComponent()->GetScaledCapsuleHalfHeight() + OtherPawn->GetCapsuleComponent()->GetScaledCapsuleHalfHeight()) * 2.0f;
				const float CombinedRadius = MyPawn->GetCapsuleComponent()->GetScaledCapsuleRadius() + OtherPawn->GetCapsuleComponent()->GetScaledCapsuleRadius();
				const FVector OtherLocation = OtherPawn->GetActorLocation();

				// check if player start overlaps this pawn
				if (FMath::Abs(SpawnLocation.Z - OtherLocation.Z) < CombinedHeight && (SpawnLocation - OtherLocation).Size2D() < CombinedRadius)
				{
					return false;
				}
			}
		}
	}
	else
	{
		return false;
	}

	return true;
}

void AValorGameMode::BeginPlay()
{
	Super::BeginPlay();

	GetWorld()->GetTimerManager().SetTimer(TimerHandle_LaneMinion, this, &AValorGameMode::SpawnLaneMinions, GetWorld()->GetWorldSettings()->GetEffectiveTimeDilation() * LaneMinionWaveInterval, true, GetWorld()->GetWorldSettings()->GetEffectiveTimeDilation() * LaneMinionStartTime);
	GetWorld()->GetTimerManager().SetTimer(TimerHandle_JungleMinion, this, &AValorGameMode::SpawnJungleMinions, GetWorld()->GetWorldSettings()->GetEffectiveTimeDilation() * JungleMinionStartTime, false);
}

void AValorGameMode::EndPlay(const EEndPlayReason::Type EndPlayReason)
{
	Super::EndPlay(EndPlayReason);

	GetWorld()->GetTimerManager().ClearTimer(TimerHandle_LaneMinion);
}

uint8 AValorGameMode::GetMaximumPlayers() const
{
	return 10;
}
uint8 AValorGameMode::GetMaximumLevel() const
{
	return 20;
}

void AValorGameMode::SpawnLaneMinions()
{
	UE_LOG(LogValorServer, Log, TEXT("Spawning lane minions."));

	for (TActorIterator<AValorLaneSpawner> It(GetWorld()); It; ++It)
	{
		(*It)->SpawnUnit();
	}
}

void AValorGameMode::SpawnJungleMinions()
{
	UE_LOG(LogValorServer, Log, TEXT("Spawning jungle minions."));

	for (TActorIterator<AValorJungleSpawner> It(GetWorld()); It; ++It)
	{
		(*It)->SpawnUnit();
	}
}