// Fill out your copyright notice in the Description page of Project Settings.

#include "Weapons/Weapon.h"
#include "Components/SkeletalMeshComponent.h"
#include "Components/SphereComponent.h"

// Sets default values
AWeapon::AWeapon()
{
	PrimaryActorTick.bCanEverTick = false;

	bReplicates = true;
	WeaponMesh = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("Weapon Mesh"));
	WeaponMesh->SetupAttachment(RootComponent);
	SetRootComponent(WeaponMesh);

	WeaponMesh->SetCollisionResponseToAllChannels(ECollisionResponse::ECR_Block);
	WeaponMesh->SetCollisionResponseToChannel(ECollisionChannel::ECC_Pawn, ECollisionResponse::ECR_Ignore);
	WeaponMesh->SetCollisionEnabled(ECollisionEnabled::NoCollision);

	Area = CreateDefaultSubobject<USphereComponent>(TEXT("AreaSphere"));
	Area->SetupAttachment(RootComponent);
	Area->SetCollisionResponseToAllChannels(ECollisionResponse::ECR_Ignore);
	Area->SetCollisionEnabled(ECollisionEnabled::NoCollision);
}

void AWeapon::BeginPlay()
{
	Super::BeginPlay();
	if (HasAuthority())
	{
		Area->SetCollisionEnabled(ECollisionEnabled::QueryAndPhysics);
		Area->SetCollisionResponseToChannel(ECollisionChannel::ECC_Pawn, ECollisionResponse::ECR_Overlap);
	}
}

// Called every frame
void AWeapon::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}
