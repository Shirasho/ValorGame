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

AValorPlayerController::AValorPlayerController(const FObjectInitializer& ObjectInitializer)
    : Super(ObjectInitializer)
{
	bShowMouseCursor = true;
	DefaultMouseCursor = EMouseCursor::Hand;

	PlayerCameraManagerClass = AValorPlayerCameraManager::StaticClass();
	CheatClass = UValorCheatManager::StaticClass();

	bEnableMouseOverEvents = true;

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
	DECLARE_SCOPE_CYCLE_COUNTER(TEXT("AValorPlayerController::OnWindowReceivedFocus"), STAT_ValorPlayerController_OnWindowReceivedFocus, STATGROUP_ValorCamera);

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
			ValorHeroCharacterProxy->ServerCreatePlayer();
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
	if (GetNetMode() != NM_DedicatedServer)
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

void AValorPlayerController::OnPrimaryAction1Pressed()
{

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

		DECLARE_SCOPE_CYCLE_COUNTER(TEXT("AValorPlayerController::OnPrimaryAction2Pressed"), STAT_ValorPlayerController_OnPrimaryAction2Pressed, STATGROUP_ValorPlayer);

		// Trace to see what is under the mouse cursor
		FHitResult HitResult;
		GetHitResultUnderCursor(ECC_Visibility, false, HitResult);

		if (HitResult.GetActor() && GetValorHeroCharacterProxy())
		{
			IValorClickableInterface* ClickableInterface = Cast<IValorClickableInterface>(HitResult.GetActor());

			// If the hit unit is clickable...
			if (ClickableInterface)
			{
				IValorUnitInterface* UnitInterface = Cast<IValorUnitInterface>(HitResult.GetActor());

				// If the hit unit is an actual unit...
				if (UnitInterface)
				{
					const AValorPlayerState* ValorPlayerState = Cast<AValorPlayerState>(PlayerState);
					check(PlayerState);

					// If the hit unit is on the same team we ignore the unit and simply move there.
					if (ValorPlayerState->GetPlayerTeam() == UnitInterface->GetTeam())
					{
						GetValorHeroCharacterProxy()->OnCharacterMovement(HitResult);
						// Only recall this method if right-clicking was a successful movement call.
						GetWorld()->GetTimerManager().SetTimer(TimerHandle_MoveToCursor, this, &AValorPlayerController::OnPrimaryAction2Pressed, GetWorldSettings()->GetEffectiveTimeDilation() * 0.45f, false);
					}
					// The hit unit is an enemy. Trigger Move-Attack.
					else
					{
						GetValorHeroCharacterProxy()->OnCharacterAttack(HitResult);
					}
				}
				// The hit unit is interactable but isn't a unit. Move next to it
				// then interact with it.
				else
				{
					GetValorHeroCharacterProxy()->OnCharacterInteract(HitResult);
					// Only recall this method if right-clicking was a successful movement call.
					GetWorld()->GetTimerManager().SetTimer(TimerHandle_MoveToCursor, this, &AValorPlayerController::OnPrimaryAction2Pressed, GetWorldSettings()->GetEffectiveTimeDilation() * 0.45f, false);
				}
			}
			// No clickable unit was hit. Assume simple move to point.
			else
			{
				GetValorHeroCharacterProxy()->OnCharacterMovement(HitResult);
				// Only recall this method if right-clicking was a successful movement call.
				GetWorld()->GetTimerManager().SetTimer(TimerHandle_MoveToCursor, this, &AValorPlayerController::OnPrimaryAction2Pressed, GetWorldSettings()->GetEffectiveTimeDilation() * 0.45f, false);
			}
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