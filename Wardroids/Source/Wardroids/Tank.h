// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include "Tank.generated.h" //Must be the final include


//Forward declarations
class UTankBarrelComponent;
class UTurretComponent;
class UTurretAimingComponent;
class AProjectile;


UCLASS()
class WARDROIDS_API ATank : public APawn
{
	GENERATED_BODY()

public:
	ATank();

	void AimAtLocation( FVector HitLocation );

	UFUNCTION( BlueprintCallable, Category = Attack )
	void FireMainGun();

protected:
	UTurretAimingComponent* TurretAimComponent = nullptr;

private:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent( class UInputComponent* PlayerInputComponent ) override;
	
	UFUNCTION( BlueprintCallable, Category = Setup )
	void SetBarrelReference( UTankBarrelComponent* NewBarrel );

	UFUNCTION( BlueprintCallable, Category = Setup )
	void SetTurretReference( UTurretComponent* NewTurret );

	UPROPERTY( EditAnywhere, Category = Attack )
	float ProjectileLaunchVelocity = 40000.0f;

	UPROPERTY( EditAnywhere, Category = Attack ) 
	float FireDelay = 1.5f;

	float LastFire = 0.0f;

	UTankBarrelComponent* Barrel = nullptr;

	UPROPERTY( EditDefaultsOnly, Category = Attack )
	TSubclassOf<AProjectile> ProjectileBlueprint;
};
