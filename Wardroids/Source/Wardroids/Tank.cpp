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
	UE_LOG( LogTemp, Warning, TEXT("Tank %s fires!"), *GetOwner()->GetName() );
	
	FVector SpawnLocation = Barrel->GetSocketLocation("ProjectileSpawnLocation");
	FRotator SpawnRotation = Barrel->GetSocketRotation("ProjectileSpawnLocation");
	
	//Spawn projectile
	GetWorld()->SpawnActor<AProjectile>( ProjectileBlueprint, 
										 SpawnLocation, 
										 SpawnRotation );
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