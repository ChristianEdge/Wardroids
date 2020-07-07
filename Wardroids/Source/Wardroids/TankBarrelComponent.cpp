// Fill out your copyright notice in the Description page of Project Settings.


#include "TankBarrelComponent.h"


void UTankBarrelComponent::Elevate( float RelativeSpeed )
{
    //UE_LOG(LogTemp, Warning, TEXT("Barreal Elevated at %.2f degrees per second"), RelativeSpeed);

    RelativeSpeed = FMath::Clamp<float>( RelativeSpeed, -1.0f, 1.0f );

    auto ElevationChange = RelativeSpeed * MaxDegreesPerSecond * GetWorld()->DeltaTimeSeconds;
    auto RawElevation = GetRelativeRotation().Pitch + ElevationChange;
    auto Elevation = FMath::Clamp<float>( RawElevation, MinElevationDegrees, MaxElevationDegrees );

    SetRelativeRotation( FRotator( Elevation, .0f, .0f ) );

}