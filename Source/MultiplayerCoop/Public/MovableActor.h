// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "MovableActor.generated.h"

UCLASS()
class MULTIPLAYERCOOP_API AMovableActor : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AMovableActor();
	virtual void Tick(float DeltaTime) override;

	UPROPERTY(VisibleAnywhere,BlueprintReadWrite)
	USceneComponent* RootComp;

	UPROPERTY(VisibleAnywhere,BlueprintReadWrite)
	class UStaticMeshComponent* Mesh;

	UPROPERTY(VisibleAnywhere,BlueprintReadWrite)
	class UTransporter* Transporter;

	UPROPERTY(VisibleAnywhere,BlueprintReadWrite)
	class UArrowComponent* Point1;

	UPROPERTY(VisibleAnywhere,BlueprintReadWrite)
	class UArrowComponent* Point2;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

private:	


};
