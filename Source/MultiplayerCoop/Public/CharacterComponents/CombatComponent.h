// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "CombatComponent.generated.h"

UCLASS(ClassGroup = (Custom), meta = (BlueprintSpawnableComponent))
class MULTIPLAYERCOOP_API UCombatComponent : public UActorComponent
{
	GENERATED_BODY()

public:
	UCombatComponent();
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction *ThisTickFunction) override;
	friend class AMultiplayerCoopCharacter;

	void EquipWeapon(class AWeapon *WeaponToEquip);

protected:
	virtual void BeginPlay() override;

public:
private:
	class AMultiplayerCoopCharacter *Character;
	AWeapon *EquippedWeapon;
};
