// Fill out your copyright notice in the Description page of Project Settings.

#include "TurretAimingComponent.h"
#include "TankBarrelComponent.h"
#include "TurretComponent.h"
#include "Kismet/GameplayStatics.h"

// Sets default values for this component's properties
UTurretAimingComponent::UTurretAimingComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = false;

	// ...
}


// Called when the game starts
void UTurretAimingComponent::BeginPlay()
{
	Super::BeginPlay();
}


void UTurretAimingComponent::Aim( FVector TargetLocation, float ProjectileLaunchVelocity )
{
	if ( !Barrel || !Turret )  { return; }
	
	/*
	auto BarrelLocation = Barrel->GetComponentLocation().ToString();
	UE_LOG(LogTemp, Warning, TEXT("Tank %s aims at location %s from %s. Projectile launch speed = %.2f m/s"), 
													*GetOwner()->GetName(), 
													*TargetLocation.ToString(), 
													*BarrelLocation, 
													ProjectileLaunchVelocity);
	*/

	FVector OutLaunchVelocity( 0 );
	FVector StartLocation = Barrel->GetSocketLocation(FName("ProjectileSpawnLocation"));

	bool bIsAimSolution = UGameplayStatics::SuggestProjectileVelocity( //Keep all parameters, doesn't work without the "false, .0f, .0f,"
												this, 
												OutLaunchVelocity,
												StartLocation,
												TargetLocation,
												ProjectileLaunchVelocity,
												false,
												.0f,
												.0f,
												ESuggestProjVelocityTraceOption::DoNotTrace );

	if (bIsAimSolution)	
	{
		auto AimDirection = OutLaunchVelocity.GetSafeNormal(); 
		//UE_LOG(LogTemp, Warning, TEXT("Tank %s has aim solution (as unit vector) : %s"), *GetOwner()->GetName(), *AimDirection.ToString());

		MoveBarrel( AimDirection );
		MoveTurret( AimDirection );
	}
	else 
	{
		UE_LOG(LogTemp, Error, TEXT("Tank %s has no aim solution!"), *GetOwner()->GetName());
	}
}

void UTurretAimingComponent::MoveBarrel( FVector AimDirection )
{
	//Get current barrel position and final direction
	auto BarrelRotator = Barrel->GetForwardVector().Rotation();
	auto AimDirectionRotator = AimDirection.Rotation();
	auto DeltaRotator = AimDirectionRotator - BarrelRotator;

	/*
	UE_LOG(LogTemp, Warning, TEXT("Tank %s aim direction  drotator = %s"), 
								*GetOwner()->GetName(), 
								*DeltaRotator.ToString()); */

	//Move a certain amount each frame given a barrel speed
	Barrel->Elevate(DeltaRotator.Pitch);
}

void UTurretAimingComponent::MoveTurret ( FVector AimDirection )
{
	//Get current barrel position and final direction
	auto BarrelRotator = Barrel->GetForwardVector().Rotation();
	auto AimDirectionRotator = AimDirection.Rotation();
	auto DeltaRotator = AimDirectionRotator - BarrelRotator;
	
	Turret->Rotate( DeltaRotator.Yaw );
}

void UTurretAimingComponent::SetBarrelReference( UTankBarrelComponent* NewBarrel )
{
	if ( NewBarrel ) { Barrel = NewBarrel; }
}

void UTurretAimingComponent::SetTurretReference( UTurretComponent* NewTurret )
{
	if ( NewTurret ) { Turret = NewTurret; }
}