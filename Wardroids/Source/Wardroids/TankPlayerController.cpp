// Fill out your copyright notice in the Description page of Project Settings.

#include "Engine/World.h"
#include "TankPlayerController.h"

#define OUT

void ATankPlayerController::BeginPlay()
{
    Super::BeginPlay();

    if (GetControlledTank() == nullptr)
    {
        UE_LOG(LogTemp, Error, TEXT("TankPlayerController is not attached to a Pawn!"));
    }
    else
    {
        //UE_LOG(LogTemp, Warning, TEXT("I am ATankPlayerController attached to Pawn: %s"), *GetControlledTank()->GetName());
    }
}

void ATankPlayerController::Tick( float DeltaTime )
{
    Super::Tick(DeltaTime);

    //Aim tank turret
    AimTowardsCrosshair();
}

ATank* ATankPlayerController::GetControlledTank() const
{
    return Cast<ATank>( GetPawn() );
}


void ATankPlayerController::AimTowardsCrosshair()
{
    if ( !GetControlledTank() ) {return;}

    FVector HitLocation; //OUT parameter 

    if ( GetSightRayHitLocation( OUT HitLocation ) )
    {
        //UE_LOG(LogTemp, Warning, TEXT("Hit Location: %s"), *HitLocation.ToString());
        GetControlledTank()->AimAtLocation( HitLocation );
    }
}

//Get a world location
bool ATankPlayerController::GetSightRayHitLocation( FVector& HitLocation ) const
{
    //Raycast from camera through crosshair to location in world, get hit result
    //If raycast hits a place in the world, tell Tank to turn turret/raise barrel towards that location
        //do this with OUT parameter FVector

    //Find the crosshair location
    int32 ViewportSizeX, ViewportSizeY;
    GetViewportSize(ViewportSizeX, ViewportSizeY);

    FVector2D CrosshairSceenLocation ( ViewportSizeX * CrosshairX, ViewportSizeY * CrosshairY );
    
    //Find the current look direction 
    FVector LookDirection;
    if  ( GetLookDirection( CrosshairSceenLocation, LookDirection )  )
    {   //UE_LOG(LogTemp, Warning, TEXT("Look Direction: %s"), *LookDirection.ToString());
        GetWorldHitLocation(LookDirection, HitLocation);
    }

    return true;
}

bool ATankPlayerController::GetLookDirection( FVector2D CrosshairSceenLocation, FVector& LookDirection ) const
{
    FVector WorldLocation;
    return DeprojectScreenPositionToWorld(
        CrosshairSceenLocation.X, 
        CrosshairSceenLocation.Y, 
        WorldLocation, 
        LookDirection);
}

bool ATankPlayerController::GetWorldHitLocation( FVector LookDirection, FVector& HitLocation ) const
{
    FHitResult TargetHit;

    FVector StartPosition = PlayerCameraManager->GetCameraLocation();
    FVector EndPosition = StartPosition + (LookDirection * LookRange);

    if  ( GetWorld()->LineTraceSingleByChannel( OUT TargetHit,
                                                StartPosition,
                                                EndPosition,
                                                ECollisionChannel::ECC_Visibility) )
    {
        HitLocation = TargetHit.Location;
        return true;
    }

    else {return false;}
}
