// Fill out your copyright notice in the Description page of Project Settings.


#include "TurretComponent.h"
#include "Engine/World.h"

void UTurretComponent::Rotate( float RelativeSpeed )
{
    RelativeSpeed = FMath::Clamp<float>( RelativeSpeed, -1.0f, 1.0f );

    auto RotationChange = RelativeSpeed * MaxDegreesPerSecond * GetWorld()->DeltaTimeSeconds;
    auto Rotation = GetRelativeRotation().Yaw + RotationChange;

    /*
    UE_LOG(LogTemp, Warning, TEXT("Tank %s Relative Rotation: %s \tRotation: %.2f"), 
        *GetOwner()->GetName(),
        *RelativeRotation.ToString(),
        Rotation);
    */

    SetRelativeRotation( FRotator( .0f, Rotation, .0f  ) );
}