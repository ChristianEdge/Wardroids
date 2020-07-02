// Fill out your copyright notice in the Description page of Project Settings.


#include "Tank.h"

// Set default values
ATank::ATank()
{
 	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	Turret = CreateDefaultSubobject<UTurretAimingComponent>(FName("TurretAimingComponent"));
}

// Called when the game starts or when spawned
void ATank::BeginPlay()
{
	Super::BeginPlay();
}

// Called every frame
void ATank::Tick( float DeltaTime )
{
	Super::Tick( DeltaTime );
}

// Called to bind functionality to input
void ATank::SetupPlayerInputComponent( UInputComponent* PlayerInputComponent )
{
	Super::SetupPlayerInputComponent( PlayerInputComponent );
}

void ATank::AimAtLocation( FVector HitLocation )
{
	//UE_LOG(LogTemp, Warning, TEXT("%s aims at %s"), *GetName(), *HitLocation.ToString());
	Turret->Aim( HitLocation, ProjectileLaunchVelocity );	
}

void ATank::SetBarrelReference( UStaticMeshComponent* NewBarrel )
{
	Turret->SetBarrelReference( NewBarrel );
}