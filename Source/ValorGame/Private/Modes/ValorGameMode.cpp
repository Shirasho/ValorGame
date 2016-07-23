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
#include "ValorAIController.h"
#include "ValorAIHeroController.h"
#include "ValorAIMinionController.h"

#include "ValorHeroCharacterProxy.h"


AValorGameMode::AValorGameMode(const FObjectInitializer& ObjectInitializer) 
	: Super(ObjectInitializer)
{
	/*static ConstructorHelpers::FClassFinder<APawn> CH_PlayerPawn(TEXT("/Game/Blueprints/Heros/Natsu_BP"));
	if (CH_PlayerPawn.Class)
	{
		DefaultPawnClass = CH_PlayerPawn.Class;
	}*/

	/*static ConstructorHelpers::FClassFinder<APawn> BotPawnOb(TEXT("/Game/Blueprints/Pawns/BotPawn"));
	DefaultAIPawnClass = BotPawnOb.Class;*/

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

	for (TActorIterator<APlayerStart> It(GetWorld()); It; ++It)
	{
		APlayerStart* TestSpawn = *It;
		if (TestSpawn->IsA<APlayerStartPIE>())
		{
			// Always prefer the first "Play from Here" PlayerStart, if we find one while in PIE mode.
			BestStart = TestSpawn;
			break;
		}
		else
		{
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
	}

	if (!BestStart)
	{
		if (PreferredSpawns.Num() > 0)
		{
			BestStart = PreferredSpawns[FMath::RandHelper(PreferredSpawns.Num())];
		}
		else if (FallbackSpawns.Num() > 0)
		{
			BestStart = FallbackSpawns[FMath::RandHelper(FallbackSpawns.Num())];
		}
	}

	return BestStart ? BestStart : Super::ChoosePlayerStart_Implementation(Player);
}

UClass* AValorGameMode::GetDefaultPawnClassForController_Implementation(AController* InController)
{
	AValorAIController* ValorAIController = Cast<AValorAIController>(InController);
	if (ValorAIController)
	{
		if (ValorAIController->IsA<AValorAIHeroController>())
		{
			return DefaultAIPawnClass;
		}
		else if (ValorAIController->IsA <AValorAIMinionController>())
		{
			if (ValorAIController->GetValorAICharacter()->GetTeam() == EValorTeam::One)
			{
				return TeamOneMinionClass;
			}
			else if (ValorAIController->GetValorAICharacter()->GetTeam() == EValorTeam::Two)
			{
				return TeamTwoMinionClass;
			}
			else if (ValorAIController->GetValorAICharacter()->GetTeam() == EValorTeam::Three)
			{
				return TeamThreeMinionClass;
			}
			else if (ValorAIController->GetValorAICharacter()->GetTeam() == EValorTeam::Four)
			{
				return TeamFourMinionClass;
			}
			else
			{
				return DefaultAIPawnClass;
			}
		}
	}

	return Super::GetDefaultPawnClassForController_Implementation(InController);
}

bool AValorGameMode::IsPlayerStartAllowed(APlayerStart* SpawnPoint, AController* Player) const
{
	const AValorPlayerStart* ValorSpawnPoint = Cast<AValorPlayerStart>(SpawnPoint);
	if (ValorSpawnPoint)
	{
		const AValorAIController* ValorAIController = Cast<AValorAIController>(Player);
		if (ValorAIController)
		{
			return ValorSpawnPoint->bCanSpawnMinions && ((static_cast<uint8>(ValorAIController->GetValorAICharacter()->GetTeam()) & ValorSpawnPoint->SpawnTeam) > 0);
		}

		const AValorPlayerController* ValorPlayerController = Cast<AValorPlayerController>(Player);
		if (ValorPlayerController)
		{
			return ValorSpawnPoint->bCanSpawnMinions && ((static_cast<uint8>(ValorPlayerController->GetValorHeroCharacter()->GetTeam()) & ValorSpawnPoint->SpawnTeam) > 0);
		}
	}

	return false;
}

bool AValorGameMode::IsPlayerStartPreferred(APlayerStart* SpawnPoint, AController* Player) const
{
	ACharacter* MyPawn = Cast<ACharacter>((*DefaultPawnClass)->GetDefaultObject<ACharacter>());
	AValorAIController* AIController = Cast<AValorAIController>(Player);
	if (AIController)
	{
		MyPawn = Cast<ACharacter>(DefaultAIPawnClass->GetDefaultObject<ACharacter>());
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