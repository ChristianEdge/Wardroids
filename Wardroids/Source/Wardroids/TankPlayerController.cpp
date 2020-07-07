// Fill out your copyright notice in the Description page of Project Settings.

#include "TankPlayerController.h"
#include "Tank.h"
#include "Engine/World.h"


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
    if ( GetSightRayHitLocation( HitLocation ) )
    {
        //UE_LOG(LogTemp, Warning, TEXT("Hit Location: %s"), *HitLocation.ToString());
        GetControlledTank()->AimAtLocation( HitLocation );
    }
}

//Get a world location
bool ATankPlayerController::GetSightRayHitLocation( FVector& HitLocation ) const
{
    //Raycast (line trace) from camera through UI crosshair to a XYZ location in world, out as HitLocation

    //Find the crosshair position in the viewport
    int32 ViewportSizeX, ViewportSizeY; 
    GetViewportSize( ViewportSizeX, ViewportSizeY ); //Out parameters
    FVector2D CrosshairSceenLocation ( ViewportSizeX * CrosshairX, ViewportSizeY * CrosshairY );
    
    //Find the current look direction 
    FVector LookDirection;
    if  ( GetLookDirection( CrosshairSceenLocation, LookDirection )  )
    {   
        //UE_LOG(LogTemp, Warning, TEXT("Look Direction: %s"), *LookDirection.ToString());
        GetWorldHitLocation( LookDirection, HitLocation );
    }

    return true;
}

bool ATankPlayerController::GetLookDirection( FVector2D CrosshairSceenLocation, FVector& LookDirection ) const
{
    FVector WorldLocation;
    return DeprojectScreenPositionToWorld(  CrosshairSceenLocation.X, 
                                            CrosshairSceenLocation.Y, 
                                            WorldLocation, 
                                            LookDirection); // out parameter
}

bool ATankPlayerController::GetWorldHitLocation( FVector LookDirection, FVector& HitLocation ) const
{
    FHitResult TargetHit;

    FVector StartPosition = PlayerCameraManager->GetCameraLocation();
    FVector EndPosition = StartPosition + (LookDirection * LookRange);

    bool bIsLineTracable = GetWorld()->LineTraceSingleByChannel( TargetHit,  // out parameter
                                                                 StartPosition,
                                                                 EndPosition,
                                                                 ECollisionChannel::ECC_Visibility);
    if (bIsLineTracable)
    {
        HitLocation = TargetHit.Location;
        return true;
    }
    else 
    { 
        HitLocation = FVector(0);
        return false; 
    }
}
