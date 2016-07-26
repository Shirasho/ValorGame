// Copyright Shirasho Media 2016. All rights reserved.

#include "ValorGame.h"
#include "ValorPlayerController.h"

#include "ValorPlayerCameraManager.h"
#include "ValorCheatManager.h"

#include "ValorPlayerState.h"

#include "ValorHeroCharacter.h"
#include "ValorHeroCharacterProxy.h"



AValorPlayerController::AValorPlayerController(const FObjectInitializer& ObjectInitializer)
    : Super(ObjectInitializer)
{
	bShowMouseCursor = true;
	DefaultMouseCursor = EMouseCursor::Hand;

	PlayerCameraManagerClass = AValorPlayerCameraManager::StaticClass();
	CheatClass = UValorCheatManager::StaticClass();

	bFirstTick = true;

	bReplicates = true;
}

void AValorPlayerController::PostInitializeComponents()
{
	Super::PostInitializeComponents();
}

void AValorPlayerController::BeginPlay()
{
	Super::BeginPlay();
}

void AValorPlayerController::Tick(float DeltaSeconds)
{
	Super::Tick(DeltaSeconds);

	if (bFirstTick)
	{
		bFirstTick = false;

		if (GetNetMode() != NM_DedicatedServer)
		{
			const AValorHeroCharacter* PlayerCharacter = GetValorHeroCharacter();
			if (PlayerCharacter && PlayerCharacter->GetValorHeroInitilizationProperties().MainUserInterface)
			{
				MainUserInterface = CreateWidget<UValorUserWidget>(this, PlayerCharacter->GetValorHeroInitilizationProperties().MainUserInterface);
				FInputModeGameAndUI Mode;
				//Mode.SetWidgetToFocus(MainUserInterface->GetCachedWidget());
				Mode.SetLockMouseToViewport(true);
				Mode.SetHideCursorDuringCapture(false);
				SetInputMode(Mode);
				MainUserInterface->AddToViewport(9999);
			}
		}
	}
}

void AValorPlayerController::SetupInputComponent()
{
    Super::SetupInputComponent();

    check(InputComponent);

    /* OnLeftMouse */
    InputComponent->BindAction("PrimaryAction1", IE_Pressed, this, &AValorPlayerController::OnPrimaryAction1Pressed);
    InputComponent->BindAction("PrimaryAction1", IE_Released, this, &AValorPlayerController::OnPrimaryAction1Released);

    /* OnRightMouse */
    InputComponent->BindAction("PrimaryAction2", IE_Pressed, this, &AValorPlayerController::OnPrimaryAction2Pressed);
    InputComponent->BindAction("PrimaryAction2", IE_Released, this, &AValorPlayerController::OnPrimaryAction2Released);

    /* OnMouseWheel */
    InputComponent->BindAction("CameraZoomIn", IE_Pressed, this, &AValorPlayerController::OnCameraZoomInPressed);
    InputComponent->BindAction("CameraZoomOut", IE_Pressed, this, &AValorPlayerController::OnCameraZoomOutPressed);

    /* OnAbilityCast */
    InputComponent->BindAction("AbilityAction1", IE_Pressed, this, &AValorPlayerController::OnAbilityAction1Pressed);
    InputComponent->BindAction("AbilityAction1", IE_Released, this, &AValorPlayerController::OnAbilityAction1Released);

    InputComponent->BindAction("AbilityAction2", IE_Pressed, this, &AValorPlayerController::OnAbilityAction2Pressed);
    InputComponent->BindAction("AbilityAction2", IE_Released, this, &AValorPlayerController::OnAbilityAction2Released);

    InputComponent->BindAction("AbilityAction3", IE_Pressed, this, &AValorPlayerController::OnAbilityAction3Pressed);
    InputComponent->BindAction("AbilityAction3", IE_Released, this, &AValorPlayerController::OnAbilityAction3Released);

    InputComponent->BindAction("AbilityAction4", IE_Pressed, this, &AValorPlayerController::OnAbilityAction4Pressed);
    InputComponent->BindAction("AbilityAction4", IE_Released, this, &AValorPlayerController::OnAbilityAction4Released);

    InputComponent->BindAction("AbilitySpell1", IE_Pressed, this, &AValorPlayerController::OnAbilitySpell1Pressed);
    InputComponent->BindAction("AbilitySpell1", IE_Released, this, &AValorPlayerController::OnAbilitySpell1Released);

    InputComponent->BindAction("AbilitySpell2", IE_Pressed, this, &AValorPlayerController::OnAbilitySpell2Pressed);
    InputComponent->BindAction("AbilitySpell2", IE_Released, this, &AValorPlayerController::OnAbilitySpell2Released);

    /* OnItemCast */
    InputComponent->BindAction("UseItem1", IE_Pressed, this, &AValorPlayerController::OnUseItem1Pressed);
    InputComponent->BindAction("UseItem2", IE_Pressed, this, &AValorPlayerController::OnUseItem2Pressed);
    InputComponent->BindAction("UseItem3", IE_Pressed, this, &AValorPlayerController::OnUseItem3Pressed);

    /* OnCameraPanPrecise */
    InputComponent->BindAction("CameraLocation1", IE_Pressed, this, &AValorPlayerController::OnCameraPanPrecise1Pressed);
    InputComponent->BindAction("CameraLocation2", IE_Pressed, this, &AValorPlayerController::OnCameraPanPrecise2Pressed);
    InputComponent->BindAction("CameraLocation3", IE_Pressed, this, &AValorPlayerController::OnCameraPanPrecise3Pressed);
    InputComponent->BindAction("CameraLocation4", IE_Pressed, this, &AValorPlayerController::OnCameraPanPrecise4Pressed);

    /* OnCameraPan */
    InputComponent->BindAction("PanCameraLeft", IE_Pressed, this, &AValorPlayerController::OnCameraPanLeftPressed);
    InputComponent->BindAction("PanCameraLeft", IE_Released, this, &AValorPlayerController::OnCameraPanLeftReleased);

    InputComponent->BindAction("PanCameraRight", IE_Pressed, this, &AValorPlayerController::OnCameraPanRightPressed);
    InputComponent->BindAction("PanCameraRight", IE_Released, this, &AValorPlayerController::OnCameraPanRightReleased);

    InputComponent->BindAction("PanCameraUp", IE_Pressed, this, &AValorPlayerController::OnCameraPanUpPressed);
    InputComponent->BindAction("PanCameraUp", IE_Released, this, &AValorPlayerController::OnCameraPanUpReleased);

    InputComponent->BindAction("PanCameraDown", IE_Pressed, this, &AValorPlayerController::OnCameraPanDownPressed);
    InputComponent->BindAction("PanCameraDown", IE_Released, this, &AValorPlayerController::OnCameraPanDownReleased);

    /* OnCameraCenter */
    InputComponent->BindAction("CameraCenter", IE_Pressed, this, &AValorPlayerController::OnCameraCenterPressed);

    /* OnMenu */
    InputComponent->BindAction("ToggleMenu", IE_Pressed, this, &AValorPlayerController::OnToggleMenuPressed);
    InputComponent->BindAction("ToggleScoreboard", IE_Pressed, this, &AValorPlayerController::OnToggleScoreboardPressed);

    /* On Push-To-Talk */
    InputComponent->BindAction("PushToTalk", IE_Pressed, this, &AValorPlayerController::OnPushToTalkPressed);
    InputComponent->BindAction("PushToTalk", IE_Released, this, &AValorPlayerController::OnPushToTalkReleased);


    // Recall, emote, dance, focus chat
}

AValorHeroCharacterProxy* AValorPlayerController::GetValorHeroCharacterProxy() const
{
	return Cast<AValorHeroCharacterProxy>(GetPawn());
}

AValorHeroCharacter* AValorPlayerController::GetValorHeroCharacter() const
{
	if (GetValorHeroCharacterProxy())
	{
		return GetValorHeroCharacterProxy()->GetValorHeroCharacter();
	}
	return nullptr;
}

void AValorPlayerController::OnPrimaryAction1Pressed()
{
	//FString Message = FString::Printf(TEXT("Player health: %f"), GetValorHeroCharacter()->GetHealth());
	//VALOR_LOGF(Message);
	VALOR_LOG("Player health: %f", GetValorHeroCharacter()->GetBaseHealth());
}

void AValorPlayerController::OnPrimaryAction1Released()
{

}

void AValorPlayerController::OnPrimaryAction2Pressed()
{
	/* There would be more tests here. For prototyping
	* we are simply going to move a character. */
	
	// Trace to see what is under the mouse cursor
	FHitResult Hit;
	GetHitResultUnderCursor(ECC_Visibility, false, Hit);

	if (Hit.bBlockingHit)
	{
		ServerMoveToCursor(Hit);

		if (GetValorHeroCharacterProxy())
		{
			GetValorHeroCharacterProxy()->OnCharacterMovement();
		}

		GetWorld()->GetTimerManager().SetTimer(TimerHandle_MoveToCursor, this, &AValorPlayerController::OnPrimaryAction2Pressed, GetWorldSettings()->GetEffectiveTimeDilation() * 0.45f, false);
	}
}

void AValorPlayerController::OnPrimaryAction2Released()
{
	// If the timer is set between movement polling intervals, clear it.
	GetWorld()->GetTimerManager().ClearTimer(TimerHandle_MoveToCursor);
	//TimerHandle_MoveToCursor.MakeValid();
}

void AValorPlayerController::OnAbilityAction1Pressed()
{
	VALOR_LOG("AbilityAction1Pressed()");
}

void AValorPlayerController::OnAbilityAction1Released()
{

}

void AValorPlayerController::OnAbilityAction2Pressed()
{

}

void AValorPlayerController::OnAbilityAction2Released()
{

}

void AValorPlayerController::OnAbilityAction3Pressed()
{

}

void AValorPlayerController::OnAbilityAction3Released()
{

}

void AValorPlayerController::OnAbilityAction4Pressed()
{

}

void AValorPlayerController::OnAbilityAction4Released()
{

}

void AValorPlayerController::OnAbilitySpell1Pressed()
{

}

void AValorPlayerController::OnAbilitySpell1Released()
{

}

void AValorPlayerController::OnAbilitySpell2Pressed()
{

}

void AValorPlayerController::OnAbilitySpell2Released()
{

}

void AValorPlayerController::OnUseItem1Pressed()
{

}

void AValorPlayerController::OnUseItem2Pressed()
{

}

void AValorPlayerController::OnUseItem3Pressed()
{

}


void AValorPlayerController::OnCameraZoomInPressed()
{

}

void AValorPlayerController::OnCameraZoomOutPressed()
{

}

void AValorPlayerController::OnCameraCenterPressed()
{

}

void AValorPlayerController::OnCameraPanPrecise1Pressed()
{

}

void AValorPlayerController::OnCameraPanPrecise2Pressed()
{

}

void AValorPlayerController::OnCameraPanPrecise3Pressed()
{

}

void AValorPlayerController::OnCameraPanPrecise4Pressed()
{

}

void AValorPlayerController::OnCameraPanLeftPressed()
{

}

void AValorPlayerController::OnCameraPanLeftReleased()
{

}

void AValorPlayerController::OnCameraPanRightPressed()
{

}

void AValorPlayerController::OnCameraPanRightReleased()
{

}

void AValorPlayerController::OnCameraPanUpPressed()
{

}

void AValorPlayerController::OnCameraPanUpReleased()
{

}

void AValorPlayerController::OnCameraPanDownPressed()
{

}

void AValorPlayerController::OnCameraPanDownReleased()
{

}

void AValorPlayerController::OnToggleMenuPressed()
{

}

void AValorPlayerController::OnToggleScoreboardPressed()
{

}

void AValorPlayerController::OnPushToTalkPressed()
{

}

void AValorPlayerController::OnPushToTalkReleased()
{

}

void AValorPlayerController::ClientStartOnlineMatch_Implementation()
{
	if (!IsPrimaryPlayer())
		return;

	AValorPlayerState* ValorPlayerState = Cast<AValorPlayerState>(PlayerState);
	if (ValorPlayerState)
	{
		const IOnlineSubsystem* OnlineSubystem = IOnlineSubsystem::Get();
		if (OnlineSubystem)
		{
			IOnlineSessionPtr SessionInterface = OnlineSubystem->GetSessionInterface();
			if (SessionInterface.IsValid())
			{
				UE_LOG(LogValorClient, Log, TEXT("Starting session '%s' on client."), *ValorPlayerState->SessionName.ToString());
				SessionInterface->StartSession(ValorPlayerState->SessionName);
			}
		}
	}
	else
	{
		// Keep retrying until player state is replicated
		GetWorld()->GetTimerManager().SetTimer(TimerHandle_ClientStartOnlineGame, this, &AValorPlayerController::ClientStartOnlineMatch_Implementation, 0.2f, false);
	}
}

void AValorPlayerController::ClientEndOnlineMatch_Implementation()
{
	if (!IsPrimaryPlayer())
		return;

	const AValorPlayerState* ValorPlayerState = Cast<AValorPlayerState>(PlayerState);
	if (ValorPlayerState)
	{
		const IOnlineSubsystem* OnlineSubystem = IOnlineSubsystem::Get();
		if (OnlineSubystem)
		{
			IOnlineSessionPtr SessionInterface = OnlineSubystem->GetSessionInterface();
			if (SessionInterface.IsValid())
			{
				UE_LOG(LogValorClient, Log, TEXT("Ending session '%s' on client."), *ValorPlayerState->SessionName.ToString());
				SessionInterface->EndSession(ValorPlayerState->SessionName);
			}
		}
	}
}

bool AValorPlayerController::ServerCheat_Validate(const FString& Message)
{
	return true;
}

void AValorPlayerController::ServerCheat_Implementation(const FString& Message)
{
	if (CheatManager)
	{
		ClientMessage(ConsoleCommand(Message));
	}
}

bool AValorPlayerController::ServerMoveToCursor_Validate(const FHitResult& HitResult)
{
	return true;
}

void AValorPlayerController::ServerMoveToCursor_Implementation(const FHitResult& HitResult)
{
	MoveToCursor(HitResult);
}

void AValorPlayerController::MoveToCursor(const FHitResult& HitResult)
{
	if (HasAuthority())
	{
		AValorHeroCharacterProxy* Pawn = Cast<AValorHeroCharacterProxy>(GetPawn());
		if (Pawn)
		{
			UNavigationSystem* NavigationSystem = GetWorld()->GetNavigationSystem();
			const float Distance = FVector::Dist(HitResult.Location, Pawn->GetActorLocation());

			if (NavigationSystem && (Distance > 10.f))
			{
				Pawn->MoveToLocation(this, HitResult.Location);
			}
		}
	}
}