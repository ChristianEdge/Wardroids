// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "TurretAimingComponent.generated.h"

class UTankBarrelComponent;
class UTurretComponent;

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class WARDROIDS_API UTurretAimingComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UTurretAimingComponent();

	void SetBarrelReference( UTankBarrelComponent* NewBarrel );
	void SetTurretReference( UTurretComponent* NewTurret );

	void Aim( FVector TargetLocation, float ProjectileLaunchVelocity );
	void MoveBarrel( FVector AimDirection );
	void MoveTurret ( FVector AimDirection );

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

private:
	UTankBarrelComponent* Barrel = nullptr;
	UTurretComponent* Turret = nullptr;
};
