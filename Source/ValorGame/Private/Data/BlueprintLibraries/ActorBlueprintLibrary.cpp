// Copyright Shirasho Media 2016. All rights reserved.

#include "ValorGame.h"
#include "ActorBlueprintLibrary.h"

UActorComponent* UActorBlueprintLibrary::AttachComponentOfClass(UObject* WorldContextObject, TSubclassOf<UActorComponent> ComponentClass, AActor* Owner, FName ComponentName, USceneComponent* AttachTo, FName SocketName)
{
	if (!Owner)
	{
		return nullptr;
	}

	UActorComponent* Component = NewObject<UActorComponent>(Owner, *ComponentClass, ComponentName);
	if (!Component)
	{
		return nullptr;
	}

	Component->RegisterComponent();
	Component->OnComponentCreated();

	USceneComponent* SceneComponent = Cast<USceneComponent>(Component);
	if (SceneComponent)
	{
		SceneComponent->SetWorldLocation(Owner->GetActorLocation());
		SceneComponent->SetWorldRotation(Owner->GetActorRotation());

		USceneComponent* AttachToComponent = AttachTo ? AttachTo : Owner->GetRootComponent();

		SceneComponent->AttachToComponent(AttachToComponent, FAttachmentTransformRules::KeepWorldTransform, SocketName);
	}

	return Component;
}