// Fill out your copyright notice in the Description page of Project Settings.

#include "Transporter.h"
#include "PressurePlate.h"

// Sets default values for this component's properties
UTransporter::UTransporter()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	SetIsReplicatedByDefault(true); // for actorcomponent

	MoveTime = 3.f;
	ActivatedTriggerCount = 0;
	ArePointSet = false;

	StartPoint = FVector::Zero();
	EndPoint = FVector::Zero();
}

void UTransporter::SetPoints(FVector Point1, FVector Point2)
{
	if (Point1.Equals(Point2))
		return;
	StartPoint = Point1;
	EndPoint = Point2;
	ArePointSet = true;
}

void UTransporter::OnPressurePlateActivated()
{
	ActivatedTriggerCount++;
	FString Msg = FString::Printf(TEXT("Activated : %d"), ActivatedTriggerCount);
	GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::White, Msg);
}

void UTransporter::OnPressurePlateDeactivated()
{
	ActivatedTriggerCount--;
	FString Msg = FString::Printf(TEXT("Activated : %d"), ActivatedTriggerCount);
	GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::White, Msg);
}

// Called when the game starts
void UTransporter::BeginPlay()
{
	Super::BeginPlay();

	for (AActor *TA : TriggerActors)
	{
		APressurePlate *PressurePlateActor = Cast<APressurePlate>(TA);

		if (PressurePlateActor)
		{
			PressurePlateActor->OnActivated.AddDynamic(this, &UTransporter::OnPressurePlateActivated);
			PressurePlateActor->OnDeactivated.AddDynamic(this, &UTransporter::OnPressurePlateDeactivated);
		}
	}
}

// Called every frame
void UTransporter::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction *ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	if (TriggerActors.Num() > 0)
	{
		AllTriggerActorsTriggered = (ActivatedTriggerCount >= TriggerActors.Num());
	}

	AActor *MyOwner = GetOwner();
	if (MyOwner && MyOwner->HasAuthority() && ArePointSet)
	{

		FVector CurrentLoc = MyOwner->GetActorLocation();
		float Speed = FVector::Distance(StartPoint, EndPoint) / MoveTime;

		FVector TargetLoc = AllTriggerActorsTriggered ? EndPoint : StartPoint; // if all actors triggered then go to endpoint else go back to start point
		if (!CurrentLoc.Equals(TargetLoc))
		{

			FVector NewLoc = FMath::VInterpConstantTo(CurrentLoc, TargetLoc, DeltaTime, Speed);
			MyOwner->SetActorLocation(NewLoc);
		}
	}
}
