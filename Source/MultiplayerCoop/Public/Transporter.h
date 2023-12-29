// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "Transporter.generated.h"

UCLASS(ClassGroup = (Custom), meta = (BlueprintSpawnableComponent))
class MULTIPLAYERCOOP_API UTransporter : public UActorComponent
{
	GENERATED_BODY()

public:
	// Sets default values for this component's properties
	UTransporter();

	FVector StartPoint;
	FVector EndPoint;

	bool ArePointSet;

	UPROPERTY(EditAnywhere)
	float MoveTime;

	UPROPERTY(EditAnywhere)
	TArray<AActor *> TriggerActors;

	UPROPERTY(VisibleAnywhere)
	int ActivatedTriggerCount;

	UPROPERTY(BlueprintReadWrite, VisibleAnywhere)
	bool AllTriggerActorsTriggered;

	UFUNCTION(BlueprintCallable)
	void SetPoints(FVector Point1, FVector Point2);

	UFUNCTION()
	void OnPressurePlateActivated();

	UFUNCTION()
	void OnPressurePlateDeactivated();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction *ThisTickFunction) override;
};
