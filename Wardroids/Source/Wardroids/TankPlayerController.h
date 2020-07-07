// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "TankPlayerController.generated.h" //Must be last

class ATank;

UCLASS()
class WARDROIDS_API ATankPlayerController : public APlayerController
{
	GENERATED_BODY()

public:
	//Called once at game start 
	virtual void BeginPlay() override;
	//Called every frame
	virtual void Tick( float DeltaTime ) override;

private:

	void AimTowardsCrosshair();
	bool GetSightRayHitLocation( FVector& HitLocation ) const;
	bool GetLookDirection( FVector2D ScreenLocation, FVector& LookDirection ) const;
	bool GetWorldHitLocation( FVector LookDirection, FVector& HitLocation ) const;

	ATank* GetControlledTank() const;

	UPROPERTY(EditAnywhere)
	float CrosshairX = 0.5f; //Relative position of crosshair on screen
	//TODO Get location of actual crosshair from Widget somehow
	
	UPROPERTY(EditAnywhere)
	float CrosshairY = 0.3333f; //Relative position of crosshair on screen

	UPROPERTY(EditAnywhere)
	float LookRange = 1000000.0f;
};