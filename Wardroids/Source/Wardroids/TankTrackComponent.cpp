// Fill out your copyright notice in the Description page of Project Settings.


#include "TankTrackComponent.h"

void UTankTrackComponent::SetThrottle( float NewThrottle )
{
    UE_LOG(LogTemp, Warning, TEXT("Tank %s throttle: %f"), *GetOwner()->GetName(), NewThrottle);
}