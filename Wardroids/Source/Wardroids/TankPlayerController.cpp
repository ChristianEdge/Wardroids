// Fill out your copyright notice in the Description page of Project Settings.

#include "Engine/World.h"
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

    FVector HitLocation; //OUT parameter 

    if (GetSightRayHitLocation(OUT HitLocation))
    {
        UE_LOG(LogTemp, Warning, TEXT("Hit Location: %s"), *HitLocation.ToString());
    }

}

//Get a world location
bool ATankPlayerController::GetSightRayHitLocation(FVector& HitLocation) const
{
    //Raycast from camera to crosshair
    //If raycast hits a place in the world, tell tank to turn turret/raise barrel towards that location
        //do this with OUT parameter FVector

    //Find the crosshair location
    int32 ViewportSizeX, ViewportSizeY;
    GetViewportSize(ViewportSizeX, ViewportSizeY);

    FVector2D CrosshairSceenLocation (ViewportSizeX * CrosshairX, ViewportSizeY * CrosshairY);
    
    FVector LookDirection;
    if (GetLookDirection(CrosshairSceenLocation, LookDirection))
    {
        //UE_LOG(LogTemp, Warning, TEXT("Look Direction: %s"), *LookDirection.ToString());

        //Do a line trace through to the world
        //If we hit something (FHitResult),
            //Do something
        GetWorldHitLocation(LookDirection, HitLocation);

    }

    return true;
}

bool ATankPlayerController::GetLookDirection(FVector2D CrosshairSceenLocation, FVector& LookDirection) const
{
    FVector WorldLocation;
    return DeprojectScreenPositionToWorld(
        CrosshairSceenLocation.X, 
        CrosshairSceenLocation.Y, 
        WorldLocation, 
        LookDirection);
}

bool ATankPlayerController::GetWorldHitLocation(FVector LookDirection, FVector& HitLocation) const
{
    FHitResult TargetThatWasHit;

    FVector StartPosition = PlayerCameraManager->GetCameraLocation();
    FVector EndPosition = StartPosition + (LookDirection * LookRange);

    FCollisionQueryParams HitParams(FName(TEXT("")), false, GetOwner());
    FCollisionResponseParams ResponseParams;

    if  ( GetWorld()->LineTraceSingleByChannel(OUT TargetThatWasHit,
                                            StartPosition,
                                            EndPosition,
                                            ECollisionChannel::ECC_Visibility))
    {
        HitLocation = TargetThatWasHit.Location;
        return true;
    }

    return false;
}
