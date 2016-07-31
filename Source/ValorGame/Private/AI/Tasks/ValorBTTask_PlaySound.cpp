// Copyright Shirasho Media 2016. All rights reserved.

#include "ValorGame.h"
#include "ValorBTTask_PlaySound.h"

#include "ValorGameSingleton.h"
#include "AIController.h"

#include "ValorGameState.h"

UValorBTTask_PlaySoundMulticast::UValorBTTask_PlaySoundMulticast(const FObjectInitializer& ObjectInitializer) : Super(ObjectInitializer)
{
	NodeName = "PlaySoundMulticast";
}

EBTNodeResult::Type UValorBTTask_PlaySoundMulticast::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	const AAIController* MyController = OwnerComp.GetAIOwner();

	if (MyController)
	{
		if (AValorGameState* VGameState = MyController->GetWorld()->GetGameState<AValorGameState>())
		{
			if (const APawn* MyPawn = MyController->GetPawn())
			{
				if (SoundToPlay)
				{
					VGameState->MulticastPlaySoundAtLocation(SoundToPlay, MyPawn->GetActorLocation(), MyPawn->GetActorRotation());
					return EBTNodeResult::Succeeded;
				}
			}
		}
		else
		{
			// Fall back to UGameplayStatics in the hopes that one day it gets proper
			// replication support. This will only play on the server.
			if (const APawn* MyPawn = MyController->GetPawn())
			{
				UGameplayStatics::PlaySoundAtLocation(MyPawn->GetWorld(), SoundToPlay, MyPawn->GetActorLocation(), MyPawn->GetActorRotation());
				return EBTNodeResult::Succeeded;
			}
		}
	}

	return EBTNodeResult::Failed;
}

FString UValorBTTask_PlaySoundMulticast::GetStaticDescription() const
{
	return FString::Printf(TEXT("%s: '%s'"), *Super::GetStaticDescription(), SoundToPlay ? *SoundToPlay->GetName() : TEXT("None"));
}

#if WITH_EDITOR

FName UValorBTTask_PlaySoundMulticast::GetNodeIconName() const
{
	return FName("BTEditor.Graph.BTNode.Task.PlaySound.Icon");
}

#endif	// WITH_EDITOR