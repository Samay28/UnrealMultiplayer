// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "CollectableKey.generated.h"

UCLASS()
class MULTIPLAYERCOOP_API ACollectableKey : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ACollectableKey();

	UPROPERTY(ReplicatedUsing = OnRep_IsCollected, BlueprintReadWrite, VisibleAnywhere)
	bool IsCollected;

	UFUNCTION()
	void OnRep_IsCollected();

	UPROPERTY(VisibleAnywhere,BlueprintReadWrite)
	USceneComponent* RootComp;

	UPROPERTY(VisibleAnywhere,BlueprintReadWrite)
	class UStaticMeshComponent* Mesh;

	UPROPERTY(VisibleAnywhere,BlueprintReadWrite)
	class UCapsuleComponent* Capsule;

	void GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const override;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

};
