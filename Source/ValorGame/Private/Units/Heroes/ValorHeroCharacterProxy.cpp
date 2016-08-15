// Copyright Shirasho Media 2016. All rights reserved.

#include "ValorGame.h"
#include "ValorHeroCharacterProxy.h"

#include "ValorHeroCharacter.h"
#include "ValorPlayerState.h"

#include "ValorAIDefinitions.h"

#define VALOR_CURSOR_ZONE_SIZE 50
#define VALOR_CURSOR_ZONE_PCT .1f
#define VALOR_CURSOR_ZONE_USE_PCT 0
#define VALOR_CAMERA_PAN_SPEED 2500.f

DECLARE_CYCLE_STAT(TEXT("ValorGame ~ ProcessCameraInput"), STAT_ProcessCameraInput, STATGROUP_ValorCharacterProxy);

AValorHeroCharacterProxy::AValorHeroCharacterProxy(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer)
{
	bUseControllerRotationPitch = false;
	bUseControllerRotationYaw = false;
	bUseControllerRotationRoll = false;

	bCenterCamera = false;

	UCapsuleComponent* DummyRootComponent = CreateDefaultSubobject<UCapsuleComponent>(TEXT("DummyRootComponent"));
	DummyRootComponent->InitCapsuleSize(1.f, 1.f);
	DummyRootComponent->SetCollisionEnabled(ECollisionEnabled::NoCollision);
	DummyRootComponent->SetCollisionResponseToAllChannels(ECR_Ignore);
	RootComponent = DummyRootComponent;

	// Create a camera boom
	CameraBoomComponent = CreateDefaultSubobject<USpringArmComponent>(TEXT("CameraBoom"));
	CameraBoomComponent->SetupAttachment(RootComponent);
	CameraBoomComponent->bAbsoluteRotation = true; // Don't want arm to rotate when character does
	CameraBoomComponent->TargetArmLength = 900.f;
	CameraBoomComponent->SetRelativeRotation(FRotator::ZeroRotator);
	CameraBoomComponent->SetWorldRotation(FRotator::MakeFromEuler(FVector(0.f, -45.f, -90.f)));
	CameraBoomComponent->bDoCollisionTest = false; // Don't want to pull camera in when it collides with level

	// Create a camera
	CameraComponent = CreateDefaultSubobject<UCameraComponent>(TEXT("CameraComponent"));
	CameraComponent->SetupAttachment(CameraBoomComponent, USpringArmComponent::SocketName);
	CameraComponent->bUsePawnControlRotation = false; // Camera does not rotate relative to arm
	CameraComponent->SetOrthoWidth(1500.f);
	CameraComponent->SetProjectionMode(ECameraProjectionMode::Orthographic);
}

void AValorHeroCharacterProxy::PostInitializeComponents()
{
	Super::PostInitializeComponents();
}

void AValorHeroCharacterProxy::BeginPlay()
{
	Super::BeginPlay();
}

void AValorHeroCharacterProxy::Tick(float DeltaSeconds)
{
	Super::Tick(DeltaSeconds);

	if (GetNetMode() != NM_DedicatedServer)
	{
		// Camera
		ProcessCameraInput(DeltaSeconds);
	}
}

AValorHeroCharacter* AValorHeroCharacterProxy::GetValorHeroCharacter() const
{
	return Character;
}

void AValorHeroCharacterProxy::DisplayMovementDecal(const FHitResult& HitResult)
{
	if (Character && Character->GetValorHeroInitilizationProperties().ClickCursorDecal)
	{
		if (APlayerController* PlayerController = Cast<APlayerController>(GetController()))
		{
			FVector CursorFV = HitResult.ImpactNormal;
			FRotator CursorR = CursorFV.Rotation();

			UGameplayStatics::SpawnDecalAtLocation(this, Character->GetValorHeroInitilizationProperties().ClickCursorDecal, FVector(16.f, 32.f, 32.f), HitResult.Location, CursorR, 0.25f);
		}
	}
}

void AValorHeroCharacterProxy::ProcessCameraInput(float DeltaSeconds)
{
	SCOPE_CYCLE_COUNTER(STAT_ProcessCameraInput);
	if (Character)
	{
		if (bCenterCamera)
		{
			// Keep the proxy in sync with the actual character.
			FTransform CharacterTransform = Character->GetTransform();
			FTransform ProxyTransform = GetTransform();

			FTransform Transform;
			Transform.LerpTranslationScale3D(CharacterTransform, ProxyTransform, ScalarRegister(0.5f));

			SetActorTransform(Transform);
		}
		else
		{
			if (UGameViewportClient* ViewportClient = GetWorld()->GetGameViewport())
			{
				if (ViewportClient->Viewport && ViewportClient->Viewport->IsForegroundWindow()/*->IsFocused(ViewportClient->Viewport)*/)
				{
					FVector2D ViewportSize;
					ViewportClient->GetViewportSize(ViewportSize);

					FVector2D MousePosition;
					ViewportClient->GetMousePosition(MousePosition);

#if VALOR_CURSOR_ZONE_USE_PCT
					const int32 CursorMoveZoneSizeHorizontal = FMath::Max(25, (int32)(ViewportSize.X * VALOR_CURSOR_ZONE_PCT));
					const int32 CursorMoveZoneSizeVertical = FMath::Max(25, (int32)(ViewportSize.Y * VALOR_CURSOR_ZONE_PCT));
#else
					// VALOR_CURSOR_ZONE_SIZE assumes 1080p. Scale accordingly, but never go below 25px.
					const int32 CursorMoveZoneSizeHorizontal = FMath::Max(25, ((int32)ViewportSize.X / 1920) * VALOR_CURSOR_ZONE_SIZE);
					const int32 CursorMoveZoneSizeVertical = FMath::Max(25, ((int32)ViewportSize.Y / 1080) * VALOR_CURSOR_ZONE_SIZE);
#endif
					// Horizontal
					if (MousePosition.X <= CursorMoveZoneSizeHorizontal)
					{
						FVector Result = FMath::Lerp(FVector::ZeroVector, FVector(-VALOR_CAMERA_PAN_SPEED, 0.f, 0.f), FMath::Clamp(((float)CursorMoveZoneSizeHorizontal - MousePosition.X) / (float)CursorMoveZoneSizeHorizontal, 0.f, 1.f)) * DeltaSeconds;
						SetActorLocation(GetActorLocation() + Result);
					}
					else if (MousePosition.X >= ViewportSize.X - CursorMoveZoneSizeHorizontal)
					{
						FVector Result = FMath::Lerp(FVector::ZeroVector, FVector(VALOR_CAMERA_PAN_SPEED, 0.f, 0.f), FMath::Clamp((MousePosition.X - (float)ViewportSize.X + CursorMoveZoneSizeHorizontal) / (float)CursorMoveZoneSizeHorizontal, 0.f, 1.f)) * DeltaSeconds;
						SetActorLocation(GetActorLocation() + Result);
					}

					// Vertical
					if (MousePosition.Y <= CursorMoveZoneSizeVertical)
					{
						FVector Result = FMath::Lerp(FVector::ZeroVector, FVector(0.f, -VALOR_CAMERA_PAN_SPEED, 0.f), FMath::Clamp(((float)CursorMoveZoneSizeVertical - MousePosition.Y) / (float)CursorMoveZoneSizeVertical, 0.f, 1.f)) * DeltaSeconds;
						SetActorLocation(GetActorLocation() + Result);
					}
					else if (MousePosition.Y >= ViewportSize.Y - CursorMoveZoneSizeVertical)
					{
						FVector Result = FMath::Lerp(FVector::ZeroVector, FVector(0.f, VALOR_CAMERA_PAN_SPEED, 0.f), FMath::Clamp((MousePosition.Y - (float)ViewportSize.Y + CursorMoveZoneSizeVertical) / (float)CursorMoveZoneSizeVertical, 0.f, 1.f)) * DeltaSeconds;
						SetActorLocation(GetActorLocation() + Result);
					}
				}
			}
		}
	}
}

void AValorHeroCharacterProxy::OnCharacterMovement(const FHitResult& HitResult)
{
	DisplayMovementDecal(HitResult);
	ServerOnCharacterMovement(HitResult);
}

void AValorHeroCharacterProxy::OnCharacterAttack(const FHitResult& HitResult)
{
	ServerOnCharacterAttack(HitResult);
}

void AValorHeroCharacterProxy::OnCharacterInteract(const FHitResult& HitResult)
{
	ServerOnCharacterInteract(HitResult);
}

void AValorHeroCharacterProxy::OnCameraCenterPressed()
{
	bCenterCamera = true;
}

void AValorHeroCharacterProxy::OnCameraCenterReleased()
{
	bCenterCamera = false;
}


bool AValorHeroCharacterProxy::ServerCreatePlayer_Validate(/*const APlayerState* ControllerPlayerState*/)
{
	return true;/*ControllerPlayerState != nullptr;*/
}

void AValorHeroCharacterProxy::ServerCreatePlayer_Implementation(/*const APlayerState* ControllerPlayerState*/)
{
	if (HasAuthority())
	{
		const AValorPlayerState* MyPlayerState = Cast<AValorPlayerState>(PlayerState);
		if (MyPlayerState)
		{
			CharacterClass = MyPlayerState->HeroCharacter;
		}

		check(CharacterClass);

		// Get the current location of the player proxy.
		FVector Location = GetActorLocation();
		FRotator Rotation = GetActorRotation();

		FActorSpawnParameters SpawnParameters;
		SpawnParameters.Owner = this;
		SpawnParameters.Instigator = Instigator;
		SpawnParameters.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AdjustIfPossibleButAlwaysSpawn;

		Character = Cast<AValorHeroCharacter>(GetWorld()->SpawnActor(CharacterClass, &Location, &Rotation, SpawnParameters));
		Character->Spawn(PlayerState);
	}
}

bool AValorHeroCharacterProxy::ServerOnCharacterMovement_Validate(const FHitResult& HitResult)
{
	// No validation is needed to "right click" a location. This can
	// be anywhere on the map.
	return true;
}

void AValorHeroCharacterProxy::ServerOnCharacterMovement_Implementation(const FHitResult& HitResult)
{
	if (HasAuthority())
	{
		if (Character && Character->AIController && Character->AIController->GetBlackboardComponent())
		{
			Character->AIController->GetBlackboardComponent()->SetValueAsVector(VALOR_AI_BBKEY_MoveToLocation, HitResult.Location);
			Character->AIController->GetBlackboardComponent()->ClearValue(VALOR_AI_BBKEY_AttackActor);
			Character->AIController->GetBlackboardComponent()->ClearValue(VALOR_AI_BBKEY_ExplicitAttack);
		}
	}
}

bool AValorHeroCharacterProxy::ServerOnCharacterAttack_Validate(const FHitResult& HitResult)
{
	IValorUnitInterface* UnitInterface = Cast<IValorUnitInterface>(HitResult.GetActor());
	IValorClickableInterface* ClickableInterface = Cast<IValorClickableInterface>(HitResult.GetActor());
	if (UnitInterface && UnitInterface->IsAlive() && ClickableInterface && Character)
	{
		return Character->GetTeam() != UnitInterface->GetTeam();
	}
	return false;
}

void AValorHeroCharacterProxy::ServerOnCharacterAttack_Implementation(const FHitResult& HitResult)
{
	if (HasAuthority())
	{
		if (Character && Character->AIController && Character->AIController->GetBlackboardComponent())
		{
			VALOR_PRINT("Attempting to attack unit '%s'.", *GetNameSafe(HitResult.GetActor()));
			Character->AIController->GetBlackboardComponent()->SetValueAsBool(VALOR_AI_BBKEY_ExplicitAttack, true);
			Character->AIController->GetBlackboardComponent()->SetValueAsObject(VALOR_AI_BBKEY_AttackActor, HitResult.GetActor());
			Character->AIController->GetBlackboardComponent()->ClearValue(VALOR_AI_BBKEY_MoveToLocation);
		}
	}
}

bool AValorHeroCharacterProxy::ServerOnCharacterInteract_Validate(const FHitResult& HitResult)
{
	//@TODO
	return true;
}

void AValorHeroCharacterProxy::ServerOnCharacterInteract_Implementation(const FHitResult& HitResult)
{
	if (HasAuthority())
	{
		if (Character && Character->AIController && Character->AIController->GetBlackboardComponent())
		{
			//@TODO
		}
	}
}

void AValorHeroCharacterProxy::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);

	DOREPLIFETIME(AValorHeroCharacterProxy, Character);
}


#undef VALOR_CURSOR_ZONE_SIZE
#undef VALOR_CAMERA_PAN_SPEED