// Copyright Shirasho Media 2016. All rights reserved.

#include "ValorGame.h"
#include "ValorPlayerController.h"

#include "ValorGameViewportClient.h"

#include "ValorPlayerCameraManager.h"
#include "ValorCheatManager.h"

#include "ValorPlayerState.h"
#include "ValorLocalPlayer.h"
#include "ValorPersistentUser.h"

#include "ValorHeroCharacter.h"
#include "ValorHeroCharacterProxy.h"

DECLARE_CYCLE_STAT(TEXT("ValorGame ~ DetectMouseOver"), STAT_DetectMouseOver, STATGROUP_ValorPlayerController);

AValorPlayerController::AValorPlayerController(const FObjectInitializer& ObjectInitializer)
    : Super(ObjectInitializer)
{
	bShowMouseCursor = true;
	DefaultMouseCursor = EMouseCursor::Hand;

	PlayerCameraManagerClass = AValorPlayerCameraManager::StaticClass();
	CheatClass = UValorCheatManager::StaticClass();

	bReplicates = true;
}

void AValorPlayerController::PostInitializeComponents()
{
	Super::PostInitializeComponents();
}

void AValorPlayerController::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	//@NOTE - We need this due to (UE-22128).
	OnWindowReceivedFocus();

	if (GetNetMode() != NM_DedicatedServer)
	{
		DetectMouseOver();
	}
}

void AValorPlayerController::BeginPlay()
{
	Super::BeginPlay();

	const ULocalPlayer* LocalPlayer = Cast<ULocalPlayer>(Player);
	if (LocalPlayer)
	{
		UValorGameViewportClient* GameViewportClient = Cast<UValorGameViewportClient>(LocalPlayer->ViewportClient);
		if (GameViewportClient)
		{
			GameViewportClient->OnReceivedFocus().AddUObject(this, &AValorPlayerController::OnWindowReceivedFocus);
		}
	}

	if (HasAuthority())
	{
		ValorInitCharacter();
	}
}

void AValorPlayerController::OnWindowReceivedFocus()
{
	FInputModeGameAndUI Mode;
	Mode.SetLockMouseToViewport(true);
	Mode.SetHideCursorDuringCapture(false);
	SetInputMode(Mode);
}

void AValorPlayerController::EndPlay(const EEndPlayReason::Type EndPlayReason)
{
	Super::EndPlay(EndPlayReason);

	GetWorld()->GetTimerManager().ClearTimer(TimerHandle_MoveToCursor);
	GetWorld()->GetTimerManager().ClearTimer(TimerHandle_InitUserProperties);
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
	InputComponent->BindAction("CameraCenter", IE_Released, this, &AValorPlayerController::OnCameraCenterReleased);

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

void AValorPlayerController::ValorInitCharacter()
{
	if (HasAuthority() && !GetValorHeroCharacter())
	{
		AValorHeroCharacterProxy* ValorHeroCharacterProxy = GetValorHeroCharacterProxy();
		if (ValorHeroCharacterProxy)
		{
			ValorHeroCharacterProxy->ServerCreatePlayer(/*PlayerState*/);
			ClientValorInitUserInterface();
		}
		else
		{
			GetWorld()->GetTimerManager().SetTimer(TimerHandle_InitUserProperties, this, &AValorPlayerController::ValorInitCharacter, 0.025f, false);
		}
	}
}

void AValorPlayerController::ClientValorInitUserInterface_Implementation()
{
	if (IsLocalController())
	{
		const AValorHeroCharacter* PlayerCharacter = GetValorHeroCharacter();
		if (PlayerCharacter && PlayerCharacter->GetValorHeroInitilizationProperties().MainUserInterface)
		{
			MainUserInterface = CreateWidget<UValorMainInterfaceWidget>(this, PlayerCharacter->GetValorHeroInitilizationProperties().MainUserInterface);
			FInputModeGameAndUI Mode;
			Mode.SetLockMouseToViewport(true);
			Mode.SetHideCursorDuringCapture(false);
			SetInputMode(Mode);
			MainUserInterface->AddToViewport(9999);
		}
		// Keep attempting until the hero character is valid.
		else
		{
			GetWorld()->GetTimerManager().SetTimer(TimerHandle_InitUserProperties, this, &AValorPlayerController::ClientValorInitUserInterface_Implementation, 0.025f, false);
		}
	}
}

PRAGMA_DISABLE_OPTIMIZATION
void AValorPlayerController::DetectMouseOver()
{
	const AValorPlayerState* MyPlayerState = Cast<AValorPlayerState>(PlayerState);
	if (!PlayerState)
	{
		// No need to continue of the PlayerState is null.
		return;
	}

	SCOPE_CYCLE_COUNTER(STAT_DetectMouseOver);

	// Reset the render depth. If it is still under the mouse at the proper depth it will be hit below.
	if (CurrentlyHoveredActor.IsValid())
	{
		CurrentlyHoveredActor->GetMesh()->SetRenderCustomDepth(false);
		CurrentlyHoveredActor.Reset();
	}

	const ULocalPlayer* LocalPlayer = Cast<ULocalPlayer>(Player);
	if (LocalPlayer && (LocalPlayer->ViewportClient->Viewport && LocalPlayer->ViewportClient->Viewport->IsForegroundWindow()))
	{
		/* Detect if we clicked on a unit. If we did, display their stats. If we didn't then clear the unit stat GUI.
		* We can't simply use the first hit because we don't want to tag invisible enemy units. */
		TArray<FHitResult> Hits;
		GetHitResultsUnderCursorByChannel(UEngineTypes::ConvertToTraceType(ECC_ValorClickable), true, Hits);

		if (Hits.Num() > 0)
		{
			for (const FHitResult& Result : Hits)
			{
				if (!Result.GetActor())
				{
					continue;
				}

				const AValorCharacter* HitActor = Cast<AValorCharacter>(Result.GetActor());
				if (HitActor &&// The actor is valid.
					HitActor != GetValorHeroCharacter() && // The actor is not the player actor.
					(MyPlayerState->GetPlayerTeam() == HitActor->GetTeam() || !HitActor->IsStealthed())) // If the player is on the same team they are hoverable, else they are only hoverable if they are not stealthed.
				{
					if (HitActor->GetMesh())
					{
						HitActor->GetMesh()->SetRenderCustomDepth(true);
						HitActor->GetMesh()->CustomDepthStencilValue = static_cast<uint8>(HitActor->GetTeam());
						CurrentlyHoveredActor = HitActor;
						break;
					}
				}
			}
		}
		else
		{
			// Clear stat HUD
		}
	}
}
PRAGMA_ENABLE_OPTIMIZATION


void AValorPlayerController::OnPrimaryAction1Pressed()
{
	const ULocalPlayer* LocalPlayer = Cast<ULocalPlayer>(Player);
	if (LocalPlayer && (LocalPlayer->ViewportClient->Viewport && LocalPlayer->ViewportClient->Viewport->IsForegroundWindow()))
	{
		/* Detect if we clicked on a unit. If we did, display their stats. If we didn't then clear the unit stat GUI. 
		 * We can't simply use the first hit because we don't want to tag invisible enemy units. */
		TArray<FHitResult> Hits;
		GetHitResultsUnderCursorByChannel(UEngineTypes::ConvertToTraceType(ECC_ValorClickable), true, Hits);
		
		if (Hits.Num() > 0)
		{
			const AValorPlayerState* MyPlayerState = Cast<AValorPlayerState>(PlayerState);
			check(MyPlayerState);

			for (const FHitResult& Result : Hits)
			{
				const AValorCharacter* HitActor = Cast<AValorCharacter>(Result.GetActor());
				if (HitActor &&// The actor is valid.
				    HitActor != GetValorHeroCharacter() && // The actor is not the player actor.
					(MyPlayerState->GetPlayerTeam() == HitActor->GetTeam() || !HitActor->IsStealthed())) // If the player is on the same team they are clickable, else they are only clickable if they are not stealthed.
				{
					VALOR_PRINT("Clicked on clickable unit '%s'.", *GetNameSafe(HitActor));
					break;
				}
			}
		}
		else
		{
			// Clear stat HUD
		}
	}
}

void AValorPlayerController::OnPrimaryAction1Released()
{

}

void AValorPlayerController::OnPrimaryAction2Pressed()
{
	const ULocalPlayer* LocalPlayer = Cast<ULocalPlayer>(Player);
	if (LocalPlayer && (LocalPlayer->ViewportClient->Viewport && LocalPlayer->ViewportClient->Viewport->IsForegroundWindow()))
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
}

void AValorPlayerController::OnPrimaryAction2Released()
{
	// We want releases to trigger even when the window loses focus
	// in order to prevent automation.

	// If the timer is set between movement polling intervals, clear it.
	GetWorld()->GetTimerManager().ClearTimer(TimerHandle_MoveToCursor);
	//TimerHandle_MoveToCursor.MakeValid();
}

void AValorPlayerController::OnAbilityAction1Pressed()
{
	const ULocalPlayer* LocalPlayer = Cast<ULocalPlayer>(Player);
	if (LocalPlayer && (LocalPlayer->ViewportClient->Viewport && LocalPlayer->ViewportClient->Viewport->IsForegroundWindow()))
	{
		VALOR_PRINT("UI Test - AbilityAction1 pressed. ");
	}
}

void AValorPlayerController::OnAbilityAction1Released()
{

}

void AValorPlayerController::OnAbilityAction2Pressed()
{
	const ULocalPlayer* LocalPlayer = Cast<ULocalPlayer>(Player);
	if (LocalPlayer && (LocalPlayer->ViewportClient->Viewport && LocalPlayer->ViewportClient->Viewport->IsForegroundWindow()))
	{
		VALOR_PRINT("UI Test - AbilityAction2 pressed. ");
	}
}

void AValorPlayerController::OnAbilityAction2Released()
{

}

void AValorPlayerController::OnAbilityAction3Pressed()
{
	const ULocalPlayer* LocalPlayer = Cast<ULocalPlayer>(Player);
	if (LocalPlayer && (LocalPlayer->ViewportClient->Viewport && LocalPlayer->ViewportClient->Viewport->IsForegroundWindow()))
	{

	}
}

void AValorPlayerController::OnAbilityAction3Released()
{

}

void AValorPlayerController::OnAbilityAction4Pressed()
{
	const ULocalPlayer* LocalPlayer = Cast<ULocalPlayer>(Player);
	if (LocalPlayer && (LocalPlayer->ViewportClient->Viewport && LocalPlayer->ViewportClient->Viewport->IsForegroundWindow()))
	{

	}
}

void AValorPlayerController::OnAbilityAction4Released()
{

}

void AValorPlayerController::OnAbilitySpell1Pressed()
{
	const ULocalPlayer* LocalPlayer = Cast<ULocalPlayer>(Player);
	if (LocalPlayer && (LocalPlayer->ViewportClient->Viewport && LocalPlayer->ViewportClient->Viewport->IsForegroundWindow()))
	{

	}
}

void AValorPlayerController::OnAbilitySpell1Released()
{

}

void AValorPlayerController::OnAbilitySpell2Pressed()
{
	const ULocalPlayer* LocalPlayer = Cast<ULocalPlayer>(Player);
	if (LocalPlayer && (LocalPlayer->ViewportClient->Viewport && LocalPlayer->ViewportClient->Viewport->IsForegroundWindow()))
	{

	}
}

void AValorPlayerController::OnAbilitySpell2Released()
{

}

void AValorPlayerController::OnUseItem1Pressed()
{
	const ULocalPlayer* LocalPlayer = Cast<ULocalPlayer>(Player);
	if (LocalPlayer && (LocalPlayer->ViewportClient->Viewport && LocalPlayer->ViewportClient->Viewport->IsForegroundWindow()))
	{

	}
}

void AValorPlayerController::OnUseItem2Pressed()
{
	const ULocalPlayer* LocalPlayer = Cast<ULocalPlayer>(Player);
	if (LocalPlayer && (LocalPlayer->ViewportClient->Viewport && LocalPlayer->ViewportClient->Viewport->IsForegroundWindow()))
	{

	}
}

void AValorPlayerController::OnUseItem3Pressed()
{
	const ULocalPlayer* LocalPlayer = Cast<ULocalPlayer>(Player);
	if (LocalPlayer && (LocalPlayer->ViewportClient->Viewport && LocalPlayer->ViewportClient->Viewport->IsForegroundWindow()))
	{

	}
}


void AValorPlayerController::OnCameraZoomInPressed()
{
	const ULocalPlayer* LocalPlayer = Cast<ULocalPlayer>(Player);
	if (LocalPlayer && (LocalPlayer->ViewportClient->Viewport && LocalPlayer->ViewportClient->Viewport->IsForegroundWindow()))
	{
		if (GetValorHeroCharacterProxy())
		{
			float CurrentOrthoWidth = GetValorHeroCharacterProxy()->GetCameraComponent()->OrthoWidth;
			GetValorHeroCharacterProxy()->GetCameraComponent()->SetOrthoWidth(FMath::Clamp(CurrentOrthoWidth - VALOR_CAMERA_ORTHO_WIDTH_SCROLL, VALOR_CAMERA_ORTHO_WIDTH_MIN, VALOR_CAMERA_ORTHO_WIDTH_MAX));
		}
	}
}

void AValorPlayerController::OnCameraZoomOutPressed()
{
	const ULocalPlayer* LocalPlayer = Cast<ULocalPlayer>(Player);
	if (LocalPlayer && (LocalPlayer->ViewportClient->Viewport && LocalPlayer->ViewportClient->Viewport->IsForegroundWindow()))
	{
		if (GetValorHeroCharacterProxy())
		{
			float CurrentOrthoWidth = GetValorHeroCharacterProxy()->GetCameraComponent()->OrthoWidth;
			GetValorHeroCharacterProxy()->GetCameraComponent()->SetOrthoWidth(FMath::Clamp(CurrentOrthoWidth + VALOR_CAMERA_ORTHO_WIDTH_SCROLL, VALOR_CAMERA_ORTHO_WIDTH_MIN, VALOR_CAMERA_ORTHO_WIDTH_MAX));
		}
	}
}

void AValorPlayerController::OnCameraCenterPressed()
{
	const ULocalPlayer* LocalPlayer = Cast<ULocalPlayer>(Player);
	if (LocalPlayer && (LocalPlayer->ViewportClient->Viewport && LocalPlayer->ViewportClient->Viewport->IsForegroundWindow()))
	{
		if (GetValorHeroCharacterProxy())
		{
			GetValorHeroCharacterProxy()->OnCameraCenterPressed();
		}
	}
}

void AValorPlayerController::OnCameraCenterReleased()
{
	const ULocalPlayer* LocalPlayer = Cast<ULocalPlayer>(Player);
	if (LocalPlayer && (LocalPlayer->ViewportClient->Viewport && LocalPlayer->ViewportClient->Viewport->IsForegroundWindow()))
	{
		if (GetValorHeroCharacterProxy())
		{
			GetValorHeroCharacterProxy()->OnCameraCenterReleased();
		}
	}
}

void AValorPlayerController::OnCameraPanPrecise1Pressed()
{
	const ULocalPlayer* LocalPlayer = Cast<ULocalPlayer>(Player);
	if (LocalPlayer && (LocalPlayer->ViewportClient->Viewport && LocalPlayer->ViewportClient->Viewport->IsForegroundWindow()))
	{

	}
}

void AValorPlayerController::OnCameraPanPrecise2Pressed()
{
	const ULocalPlayer* LocalPlayer = Cast<ULocalPlayer>(Player);
	if (LocalPlayer && (LocalPlayer->ViewportClient->Viewport && LocalPlayer->ViewportClient->Viewport->IsForegroundWindow()))
	{

	}
}

void AValorPlayerController::OnCameraPanPrecise3Pressed()
{
	const ULocalPlayer* LocalPlayer = Cast<ULocalPlayer>(Player);
	if (LocalPlayer && (LocalPlayer->ViewportClient->Viewport && LocalPlayer->ViewportClient->Viewport->IsForegroundWindow()))
	{

	}
}

void AValorPlayerController::OnCameraPanPrecise4Pressed()
{
	const ULocalPlayer* LocalPlayer = Cast<ULocalPlayer>(Player);
	if (LocalPlayer && (LocalPlayer->ViewportClient->Viewport && LocalPlayer->ViewportClient->Viewport->IsForegroundWindow()))
	{

	}
}

void AValorPlayerController::OnCameraPanLeftPressed()
{
	const ULocalPlayer* LocalPlayer = Cast<ULocalPlayer>(Player);
	if (LocalPlayer && (LocalPlayer->ViewportClient->Viewport && LocalPlayer->ViewportClient->Viewport->IsForegroundWindow()))
	{

	}
}

void AValorPlayerController::OnCameraPanLeftReleased()
{
	const ULocalPlayer* LocalPlayer = Cast<ULocalPlayer>(Player);
	if (LocalPlayer && (LocalPlayer->ViewportClient->Viewport && LocalPlayer->ViewportClient->Viewport->IsForegroundWindow()))
	{

	}
}

void AValorPlayerController::OnCameraPanRightPressed()
{
	const ULocalPlayer* LocalPlayer = Cast<ULocalPlayer>(Player);
	if (LocalPlayer && (LocalPlayer->ViewportClient->Viewport && LocalPlayer->ViewportClient->Viewport->IsForegroundWindow()))
	{

	}
}

void AValorPlayerController::OnCameraPanRightReleased()
{
	const ULocalPlayer* LocalPlayer = Cast<ULocalPlayer>(Player);
	if (LocalPlayer && (LocalPlayer->ViewportClient->Viewport && LocalPlayer->ViewportClient->Viewport->IsForegroundWindow()))
	{

	}
}

void AValorPlayerController::OnCameraPanUpPressed()
{
	const ULocalPlayer* LocalPlayer = Cast<ULocalPlayer>(Player);
	if (LocalPlayer && (LocalPlayer->ViewportClient->Viewport && LocalPlayer->ViewportClient->Viewport->IsForegroundWindow()))
	{

	}
}

void AValorPlayerController::OnCameraPanUpReleased()
{
	const ULocalPlayer* LocalPlayer = Cast<ULocalPlayer>(Player);
	if (LocalPlayer && (LocalPlayer->ViewportClient->Viewport && LocalPlayer->ViewportClient->Viewport->IsForegroundWindow()))
	{

	}
}

void AValorPlayerController::OnCameraPanDownPressed()
{
	const ULocalPlayer* LocalPlayer = Cast<ULocalPlayer>(Player);
	if (LocalPlayer && (LocalPlayer->ViewportClient->Viewport && LocalPlayer->ViewportClient->Viewport->IsForegroundWindow()))
	{

	}
}

void AValorPlayerController::OnCameraPanDownReleased()
{
	const ULocalPlayer* LocalPlayer = Cast<ULocalPlayer>(Player);
	if (LocalPlayer && (LocalPlayer->ViewportClient->Viewport && LocalPlayer->ViewportClient->Viewport->IsForegroundWindow()))
	{

	}
}

void AValorPlayerController::OnToggleMenuPressed()
{
	const ULocalPlayer* LocalPlayer = Cast<ULocalPlayer>(Player);
	if (LocalPlayer && (LocalPlayer->ViewportClient->Viewport && LocalPlayer->ViewportClient->Viewport->IsForegroundWindow()))
	{

	}
}

void AValorPlayerController::OnToggleScoreboardPressed()
{
	const ULocalPlayer* LocalPlayer = Cast<ULocalPlayer>(Player);
	if (LocalPlayer && (LocalPlayer->ViewportClient->Viewport && LocalPlayer->ViewportClient->Viewport->IsForegroundWindow()))
	{

	}
}

void AValorPlayerController::OnPushToTalkPressed()
{
	const ULocalPlayer* LocalPlayer = Cast<ULocalPlayer>(Player);
	if (LocalPlayer && (LocalPlayer->ViewportClient->Viewport && LocalPlayer->ViewportClient->Viewport->IsForegroundWindow()))
	{

	}
}

void AValorPlayerController::OnPushToTalkReleased()
{
	const ULocalPlayer* LocalPlayer = Cast<ULocalPlayer>(Player);
	if (LocalPlayer && (LocalPlayer->ViewportClient->Viewport && LocalPlayer->ViewportClient->Viewport->IsForegroundWindow()))
	{

	}
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


bool AValorPlayerController::GetHitResultsUnderCursorByChannel(ETraceTypeQuery TraceChannel, bool bTraceComplex, TArray<FHitResult>& HitResults) const
{
	ULocalPlayer* LocalPlayer = Cast<ULocalPlayer>(Player);
	bool bHit = false;
	if (LocalPlayer && LocalPlayer->ViewportClient)
	{
		FVector2D MousePosition;
		if (LocalPlayer->ViewportClient->GetMousePosition(MousePosition))
		{
			bHit = GetHitResultsAtScreenPosition(MousePosition, TraceChannel, bTraceComplex, HitResults);
		}
	}

	return bHit;
}

bool AValorPlayerController::GetHitResultsUnderCursorForObjects(const TArray<TEnumAsByte<EObjectTypeQuery> > & ObjectTypes, bool bTraceComplex, TArray<FHitResult>& HitResults) const
{
	ULocalPlayer* LocalPlayer = Cast<ULocalPlayer>(Player);
	bool bHit = false;
	if (LocalPlayer && LocalPlayer->ViewportClient)
	{
		FVector2D MousePosition;
		if (LocalPlayer->ViewportClient->GetMousePosition(MousePosition))
		{
			bHit = GetHitResultsAtScreenPosition(MousePosition, ObjectTypes, bTraceComplex, HitResults);
		}
	}

	return bHit;
}

bool AValorPlayerController::GetHitResultsAtScreenPosition(const FVector2D ScreenPosition, const ECollisionChannel TraceChannel, const FCollisionQueryParams& CollisionQueryParams, TArray<FHitResult>& HitResults) const
{
	// Early out if we clicked on a HUD hitbox
	if (GetHUD() != NULL && GetHUD()->GetHitBoxAtCoordinates(ScreenPosition, true))
	{
		return false;
	}

	FVector WorldOrigin;
	FVector WorldDirection;
	if (UGameplayStatics::DeprojectScreenToWorld(this, ScreenPosition, WorldOrigin, WorldDirection) == true)
	{
		return GetWorld()->LineTraceMultiByChannel(HitResults, WorldOrigin, WorldOrigin + WorldDirection * HitResultTraceDistance, TraceChannel, CollisionQueryParams);
	}

	return false;
}

static const FName NAME_ClickableTrace("ClickableTrace");

bool AValorPlayerController::GetHitResultsAtScreenPosition(const FVector2D ScreenPosition, const ECollisionChannel TraceChannel, bool bTraceComplex, TArray<FHitResult>& HitResults) const
{
	FCollisionQueryParams CollisionQueryParams(NAME_ClickableTrace, bTraceComplex);
	return GetHitResultsAtScreenPosition(ScreenPosition, TraceChannel, CollisionQueryParams, HitResults);
}

bool AValorPlayerController::GetHitResultsAtScreenPosition(const FVector2D ScreenPosition, const ETraceTypeQuery TraceChannel, bool bTraceComplex, TArray<FHitResult>& HitResults) const
{
	return GetHitResultsAtScreenPosition(ScreenPosition, UEngineTypes::ConvertToCollisionChannel(TraceChannel), bTraceComplex, HitResults);
}

bool AValorPlayerController::GetHitResultsAtScreenPosition(const FVector2D ScreenPosition, const TArray<TEnumAsByte<EObjectTypeQuery> > & ObjectTypes, bool bTraceComplex, TArray<FHitResult>& HitResults) const
{
	// Early out if we clicked on a HUD hitbox
	if (GetHUD() != NULL && GetHUD()->GetHitBoxAtCoordinates(ScreenPosition, true))
	{
		return false;
	}

	FVector WorldOrigin;
	FVector WorldDirection;
	if (UGameplayStatics::DeprojectScreenToWorld(this, ScreenPosition, WorldOrigin, WorldDirection) == true)
	{
		FCollisionObjectQueryParams const ObjParam(ObjectTypes);
		return GetWorld()->LineTraceMultiByObjectType(HitResults, WorldOrigin, WorldOrigin + WorldDirection * HitResultTraceDistance, ObjParam, FCollisionQueryParams(NAME_ClickableTrace, bTraceComplex));
	}

	return false;
}