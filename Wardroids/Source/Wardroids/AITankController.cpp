// Fill out your copyright notice in the Description page of Project Settings.

#include "Engine/World.h"
#include "AITankController.h"

void AAITankController::BeginPlay()
{
    Super::BeginPlay();

    if (!GetControlledTank())
    {
        UE_LOG(LogTemp, Error, TEXT("AITanKController is not attached to a Pawn!"));
    }
    else
    {
        //UE_LOG(LogTemp, Warning, TEXT("I am AITankController attached to Pawn: %s"), *GetControlledTank()->GetName());
    }

    if (!GetPlayerTank())
    {
         UE_LOG(LogTemp, Error, TEXT("AITanKController can not find a FirstPlayerController!"));
    }
    else
    {
         //UE_LOG(LogTemp, Warning, TEXT("%s has targeted %s"), *GetControlledTank()->GetName(), *GetPlayerTank()->GetName());
    }
    
}

void AAITankController::Tick( float DeltaTime )
{
    Super::Tick(DeltaTime);

    //Aim crosshair at PlayerTank
    AimAtTarget(GetPlayerTank());
}

void AAITankController::AimAtTarget( ATank* Target )
{
    //Aim Turret
    GetControlledTank()->AimAtTarget( Target->GetActorLocation() );
}

ATank* AAITankController::GetControlledTank() const
{
    return Cast<ATank>(GetPawn());
}

ATank* AAITankController::GetPlayerTank() const
{
    return Cast<ATank>(GetWorld()->GetFirstPlayerController()->GetPawn());
}