// Fill out your copyright notice in the Description page of Project Settings.

#include "AITankController.h"
#include "Tank.h"
#include "Engine/World.h"


void AAITankController::BeginPlay()
{
    Super::BeginPlay();

    ControlledTank = GetControlledTank();
    FirstPlayerTank = GetPlayerTank();

    if ( !ControlledTank )
    {
        UE_LOG( LogTemp, Error, TEXT("AITanKController is not attached to a Pawn!") );
    }
    
    if ( !FirstPlayerTank )
    {
         UE_LOG( LogTemp, Error, TEXT("AITanKController can not find a FirstPlayerController!") );
    }
}

void AAITankController::Tick( float DeltaTime )
{
    Super::Tick( DeltaTime );

    if ( FirstPlayerTank )
    {
        AimAtTarget( FirstPlayerTank->GetActorLocation() );

        ControlledTank->FireMainGun();
    }
}

void AAITankController::AimAtTarget( FVector HitLocation )
{
    //Pass to Tank, Tank passes to TankAimingComponent
    ControlledTank->AimAtLocation( HitLocation );
}

ATank* AAITankController::GetControlledTank() const
{
    return Cast<ATank>(GetPawn());
}

ATank* AAITankController::GetPlayerTank() const
{
    return Cast<ATank>(GetWorld()->GetFirstPlayerController()->GetPawn());
}