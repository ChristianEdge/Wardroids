// Fill out your copyright notice in the Description page of Project Settings.


#include "TurretAimingComponent.h"

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

void UTurretAimingComponent::Aim( FVector Target ) const
{
	auto Name = GetOwner()->GetName();
	UE_LOG(LogTemp, Warning, TEXT("Tank %s aims at location %s"), *Name, *Target.ToString());
}

void UTurretAimingComponent::SetBarrelReference( UStaticMeshComponent* NewBarrel )
{
	if ( NewBarrel ) 
	{ 
		Barrel = NewBarrel; 
		auto Name = GetOwner()->GetName();
		auto BarrelLocation = Barrel->GetComponentLocation().ToString();
		UE_LOG(LogTemp, Warning, TEXT("Tank %s has a barrel at location %s"), *Name, *BarrelLocation);
	}
}