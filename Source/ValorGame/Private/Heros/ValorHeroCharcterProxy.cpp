// Copyright Shirasho Media 2016. All rights reserved.

#include "ValorGame.h"
#include "ValorHeroCharacterProxy.h"
#include "ValorHeroCharacter.h"
#include "ValorHeroAIController.h"


AValorHeroCharacterProxy::AValorHeroCharacterProxy(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer)
{
	bUseControllerRotationPitch = false;
	bUseControllerRotationYaw = false;
	bUseControllerRotationRoll = false;

	UCapsuleComponent* DummyRootComponent = CreateDefaultSubobject<UCapsuleComponent>(TEXT("DummyRootComponent"));
	DummyRootComponent->InitCapsuleSize(1.f, 1.f);
	DummyRootComponent->SetCollisionEnabled(ECollisionEnabled::NoCollision);
	DummyRootComponent->SetCollisionResponseToAllChannels(ECR_Ignore);
	RootComponent = DummyRootComponent;

	// Create a camera boom...
	CameraBoomComponent = CreateDefaultSubobject<USpringArmComponent>(TEXT("CameraBoom"));
	CameraBoomComponent->SetupAttachment(RootComponent);
	CameraBoomComponent->bAbsoluteRotation = true; // Don't want arm to rotate when character does
	CameraBoomComponent->TargetArmLength = 700.f;
	CameraBoomComponent->RelativeRotation = FRotator(-60.f, 0.f, 0.f);
	CameraBoomComponent->bDoCollisionTest = false; // Don't want to pull camera in when it collides with level

	// Create a camera...
	CameraComponent = CreateDefaultSubobject<UCameraComponent>(TEXT("TopDownCamera"));
	CameraComponent->SetupAttachment(CameraBoomComponent, USpringArmComponent::SocketName);
	CameraComponent->bUsePawnControlRotation = false; // Camera does not rotate relative to arm

	if (HasAuthority())
	{
		static ConstructorHelpers::FClassFinder<AValorHeroCharacter> CH_PlayerPawn(TEXT("/Game/Blueprints/Heros/Natsu_BP"));
		if (CH_PlayerPawn.Succeeded())
		{
			CharacterClass = CH_PlayerPawn.Class;
		}
	}
}

void AValorHeroCharacterProxy::BeginPlay()
{
	Super::BeginPlay();

	if (HasAuthority())
	{
		// Get the current location of the player proxy.
		FVector Location = GetActorLocation();
		FRotator Rotation = GetActorRotation();

		FActorSpawnParameters SpawnParameters;
		SpawnParameters.Owner = this;
		SpawnParameters.Instigator = Instigator;
		SpawnParameters.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AlwaysSpawn;

		Character = Cast<AValorHeroCharacter>(GetWorld()->SpawnActor(CharacterClass, &Location, &Rotation, SpawnParameters));

		CharacterAI = GetWorld()->SpawnActor<AValorHeroAIController>(GetActorLocation(), GetActorRotation());
		CharacterAI->Possess(Character);
	}
}

void AValorHeroCharacterProxy::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if (Character)
	{
		// Keep the proxy in sync with the actual character.
		FTransform CharacterTransform = Character->GetTransform();
		FTransform ProxyTransform = GetTransform();

		FTransform Transform;
		Transform.LerpTranslationScale3D(CharacterTransform, ProxyTransform, ScalarRegister(0.5f));

		SetActorTransform(Transform);
	}
}

void AValorHeroCharacterProxy::MoveToLocation(const AValorPlayerController* InController, const FVector& Location)
{
	if (CharacterAI)
	{
		CharacterAI->MoveToLocation(Location, 10.f, true, true, false, false);
	}
}

void AValorHeroCharacterProxy::OnCharacterMovement()
{
	DisplayMovementDecal();
}

void AValorHeroCharacterProxy::DisplayMovementDecal()
{
	if (Character && Character->MovementCursorDecal)
	{
		if (APlayerController* PlayerController = Cast<APlayerController>(GetController()))
		{
			FHitResult TraceHitResult;
			PlayerController->GetHitResultUnderCursor(ECC_Visibility, true, TraceHitResult);
			FVector CursorFV = TraceHitResult.ImpactNormal;
			FRotator CursorR = CursorFV.Rotation();

			UGameplayStatics::SpawnDecalAtLocation(this, Character->MovementCursorDecal, FVector(16.f, 32.f, 32.f), TraceHitResult.Location, CursorR, 0.25f);
		}
	}
}

AValorHeroCharacter* AValorHeroCharacterProxy::GetValorHeroCharacter() const
{
	return Character;
}

void AValorHeroCharacterProxy::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);

	DOREPLIFETIME(AValorHeroCharacterProxy, Character);
}