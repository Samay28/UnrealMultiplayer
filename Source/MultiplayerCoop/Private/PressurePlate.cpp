// Fill out your copyright notice in the Description page of Project Settings.

#include "PressurePlate.h"
#include "Components/StaticMeshComponent.h"
#include "Components/SceneComponent.h"

// Sets default values
APressurePlate::APressurePlate()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	bReplicates = true;
	SetReplicateMovement(true);

	Activated = false;

	RootComp = CreateDefaultSubobject<USceneComponent>(TEXT("RootComponent"));
	SetRootComponent(RootComp);

	TriggerShape = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Trigger"));
	TriggerShape->SetupAttachment(RootComp);
	TriggerShape->SetIsReplicated(true);
	// auto triggermesh = ConstructorHelpers::FObjectFinder (we can do this but i dont)
	TriggerShape->SetRelativeScale3D(FVector(3.3f, 3.3f, 0.2f));
	TriggerShape->SetRelativeLocation(FVector(0.0f, 0.0f, 10.0f));

	Mesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("MeshAsset"));
	Mesh->SetupAttachment(RootComp);
	Mesh->SetIsReplicated(true);
	Mesh->SetRelativeScale3D(FVector(4.f, 4.f, 0.5f));
	Mesh->SetRelativeLocation(FVector(0.0f, 0.0f, 7.2f));
}
// Called when the game starts or when spawned
void APressurePlate::BeginPlay()
{
	Super::BeginPlay();

	TriggerShape->SetVisibility(false);
	TriggerShape->SetCollisionProfileName(FName("OverlapAll"));
}

// Called every frame
void APressurePlate::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if (HasAuthority())
	{
		TArray<AActor *> OverlappingActors;
		AActor *TriggerActor = 0;
		TriggerShape->GetOverlappingActors(OverlappingActors);

		for (int32 ActorIdx = 0; ActorIdx < OverlappingActors.Num(); ++ActorIdx)
		{
			AActor *OverlappingActor = OverlappingActors[ActorIdx];
			if (OverlappingActor->ActorHasTag("TriggerActor"))
			{
				TriggerActor = OverlappingActor;
				break;
			}
		}

		if (TriggerActor)
		{
			if (!Activated)
			{
				Activated = true;
				OnActivated.Broadcast();
			}
		}
		else
		{
			if (Activated)
			{
				Activated = false;
				OnDeactivated.Broadcast();
			}
		}
	}
}
