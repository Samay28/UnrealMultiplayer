// Fill out your copyright notice in the Description page of Project Settings.

#include "Weapons/Weapon.h"
#include "Components/SkeletalMeshComponent.h"
#include "Components/SphereComponent.h"
#include "Components/WidgetComponent.h"
#include "MultiplayerCoop/MultiplayerCoopCharacter.h"
#include "Net/UnrealNetwork.h"

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

	PickupWidget = CreateDefaultSubobject<UWidgetComponent>(TEXT("Widget"));
	PickupWidget->SetupAttachment(RootComponent);
}

void AWeapon::BeginPlay()
{
	Super::BeginPlay();

	if (PickupWidget)
	{
		PickupWidget->SetVisibility(false);
	}
	if (HasAuthority())
	{
		Area->SetCollisionEnabled(ECollisionEnabled::QueryAndPhysics);
		Area->SetCollisionResponseToChannel(ECollisionChannel::ECC_Pawn, ECollisionResponse::ECR_Overlap);
		Area->OnComponentBeginOverlap.AddDynamic(this, &AWeapon::OnSphereOverlap);
		Area->OnComponentEndOverlap.AddDynamic(this, &AWeapon::OnSphereEndOverlap);
	}
}
void AWeapon::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void AWeapon::OnSphereOverlap(UPrimitiveComponent *OverlapComp, AActor *OtherActor, UPrimitiveComponent *OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult &SweepResult)
{
	AMultiplayerCoopCharacter *Character = Cast<AMultiplayerCoopCharacter>(OtherActor);
	if (Character)
	{
		Character->SetOverlappingWeapon(this);
	}
}
void AWeapon::OnSphereEndOverlap(UPrimitiveComponent *OverlapComp, AActor *OtherActor, UPrimitiveComponent *OtherComp, int32 OtherBodyIndex)
{
	AMultiplayerCoopCharacter *Character = Cast<AMultiplayerCoopCharacter>(OtherActor);
	if (Character)
	{
		Character->SetOverlappingWeapon(NULL);
	}
}

void AWeapon::SetWeaponState(EWeaponState State)
{
	WeaponState = State;
	switch (WeaponState)
	{
	case EWeaponState::EWS_Equipped:
		ShowPickupWidget(false);
		Area->SetCollisionEnabled(ECollisionEnabled::NoCollision);
		break;
	}
}
void AWeapon::OnRep_WeaponState()
{
	switch (WeaponState)
	{
	case EWeaponState::EWS_Equipped:
		ShowPickupWidget(false);
		// Area->SetCollisionEnabled(ECollisionEnabled::NoCollision);
		break;
	}
}
void AWeapon::ShowPickupWidget(bool bShowWidget)
{
	if (PickupWidget)
	{
		PickupWidget->SetVisibility(bShowWidget);
	}
}
void AWeapon::GetLifetimeReplicatedProps(TArray<FLifetimeProperty> &OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);

	DOREPLIFETIME(AWeapon, WeaponState);
}
