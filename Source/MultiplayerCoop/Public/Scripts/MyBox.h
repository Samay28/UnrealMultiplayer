// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Particles/ParticleSystem.h"
#include "MyBox.generated.h"

UCLASS()
class MULTIPLAYERCOOP_API AMyBox : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AMyBox();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	UPROPERTY(ReplicatedUsing = OnRep_ReplicatedValue, BlueprintReadWrite)
	float ReplicatedValue;

	UFUNCTION(BlueprintCallable)
	void OnRep_ReplicatedValue();

	UFUNCTION(NetMulticast,reliable)
	void MyMulticastFunction();

	void GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const override; //chaap lo 

	FTimerHandle TestTimer;
	void DecreaseReplicatedVar();

	UPROPERTY(EditAnywhere)
	UParticleSystem* ExplosionEffect;
};
