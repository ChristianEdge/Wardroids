// Fill out your copyright notice in the Description page of Project Settings.

#include "Tank.h"
#include "Engine/World.h"
#include "Projectile.h"
#include "TankBarrelComponent.h"
#include "TurretAimingComponent.h"

// Set default values
ATank::ATank()
{
 	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;

	TurretAimComponent = CreateDefaultSubobject<UTurretAimingComponent>(FName("TurretAimingComponent"));
}

// Called when the game starts or when spawned
void ATank::BeginPlay()
{
	Super::BeginPlay();
}

// Called to bind functionality to input
void ATank::SetupPlayerInputComponent( UInputComponent* PlayerInputComponent )
{
	Super::SetupPlayerInputComponent( PlayerInputComponent );
}

void ATank::AimAtLocation( FVector HitLocation )
{
	//UE_LOG(LogTemp, Warning, TEXT("%s aims at %s"), *GetName(), *HitLocation.ToString());
	TurretAimComponent->Aim( HitLocation, ProjectileLaunchVelocity );	
}

void ATank::FireMainGun()
{	
	auto Time = GetWorld()->GetTimeSeconds(); //FPlatformTime::Seconds();
	if ( Time >  (LastFire + FireDelay) )
	{
		//Spawn projectile
		auto Projectile = GetWorld()->SpawnActor<AProjectile>( ProjectileBlueprint, 
			Barrel->GetSocketLocation("ProjectileSpawnLocation"), 
			Barrel->GetSocketRotation("ProjectileSpawnLocation") );

		Projectile->LaunchProjectile( ProjectileLaunchVelocity );
		LastFire = Time;
	}
}

void ATank::SetBarrelReference( UTankBarrelComponent* NewBarrel )
{
	if ( !NewBarrel ) { return; }
	TurretAimComponent->SetBarrelReference( NewBarrel );
	Barrel = NewBarrel;
}

void ATank::SetTurretReference( UTurretComponent* NewTurret )
{
	if ( !NewTurret ) { return; }
	TurretAimComponent->SetTurretReference( NewTurret );
}