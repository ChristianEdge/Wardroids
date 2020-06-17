// Fill out your copyright notice in the Description page of Project Settings.


#include "TankPlayerController.h"

#define OUT

void ATankPlayerController::BeginPlay()
{
    Super::BeginPlay();

    Tank = GetControlledTank();

    if (Tank == nullptr)
    {
        UE_LOG(LogTemp, Error, TEXT("TankPlayerController is not attached to a Pawn!"));
    }
    else
    {
        UE_LOG(LogTemp, Warning, TEXT("I am ATankPlayerController attached to Pawn: %s"), *Tank->GetName());
    }
}

void ATankPlayerController::Tick(float DeltaTime)
{
    Super::Tick(DeltaTime);

    //Aim crosshair at PlayerTank
    AimTowardsCrosshair();
}

ATank* ATankPlayerController::GetControlledTank() const
{
    return Cast<ATank>(GetPawn());
}


void ATankPlayerController::AimTowardsCrosshair()
{
    if (Tank == nullptr) {return;}
 
    //Aim Turret

    FVector HitLoc; //OUT parameter 

    if (!GetSightRayHitLocation(OUT HitLoc))
    {
         UE_LOG(LogTemp, Warning, TEXT("Hit Location: %s"), *HitLoc.ToString());
    }
}

bool ATankPlayerController::GetSightRayHitLocation(FVector& HitLocation) const
{
    HitLocation = FVector(1.0);
    //Raycast from camera to crosshair
    //If raycast hits a place in the world, tell tank to turn turret/raise barrel towards that location
        //do this with OUT parameter FVector
    return false;
}