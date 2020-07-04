// Fill out your copyright notice in the Description page of Project Settings.


#include "TankBarrelComponent.h"


void UTankBarrelComponent::Elevate( float DegreesPerSecond )
{
    UE_LOG(LogTemp, Warning, TEXT("Barreal Elevated at %.2f degrees per second"), DegreesPerSecond);
}