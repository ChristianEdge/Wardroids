// Fill out your copyright notice in the Description page of Project Settings.

#include "TurretAimingComponent.h"
#include "Kismet/GameplayStatics.h"

// Sets default values for this component's properties
UTurretAimingComponent::UTurretAimingComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}


// Called when the game starts
void UTurretAimingComponent::BeginPlay()
{
	Super::BeginPlay();
}


// Called every frame
void UTurretAimingComponent::TickComponent( float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction )
{
	Super::TickComponent( DeltaTime, TickType, ThisTickFunction );

	// ...
}

void UTurretAimingComponent::Aim( FVector TargetLocation, float ProjectileLaunchVelocity ) const
{
	if ( !Barrel )  { return; }

	float a = 0;
	
	auto BarrelLocation = Barrel->GetComponentLocation().ToString();
	UE_LOG(LogTemp, Warning, TEXT("Tank %s aims at location %s from %s. Projectile launch speed = %.2f m/s"), 
													*GetOwner()->GetName(), 
													*TargetLocation.ToString(), 
													*BarrelLocation, 
													ProjectileLaunchVelocity);

	FVector OutLaunchVelocity;
	FVector StartLocation = Barrel->GetSocketLocation(FName("ProjectileSpawnLocation"));

	bool bIsAimSolution = UGameplayStatics::SuggestProjectileVelocity( 
		this, 
		OutLaunchVelocity,
		StartLocation,
		TargetLocation,
		ProjectileLaunchVelocity, 
		ESuggestProjVelocityTraceOption::TraceFullPath );

	if (bIsAimSolution)	
	{
		auto AimDirection = OutLaunchVelocity.GetSafeNormal();

		//MoveBarrel()
	}
}

void UTurretAimingComponent::SetBarrelReference( UStaticMeshComponent* NewBarrel )
{
	if ( NewBarrel ) 
	{ 
		Barrel = NewBarrel; 
	}
}