// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Tank.h"
#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "TankPlayerController.generated.h" //Must be last


UCLASS()
class WARDROIDS_API ATankPlayerController : public APlayerController
{
	GENERATED_BODY()

public:
	virtual void BeginPlay() override;
	virtual void Tick( float DeltaTime ) override;

	void AimTowardsCrosshair();
	bool GetSightRayHitLocation( FVector& HitLocation ) const;
	bool GetLookDirection( FVector2D ScreenLocation, FVector& LookDirection ) const;
	bool GetWorldHitLocation( FVector LookDirection, FVector& HitLocation ) const;

	ATank* GetControlledTank() const;

	UPROPERTY(EditAnywhere)
	float CrosshairX = 0.5f; //Relative position of crosshair on screen
	
	UPROPERTY(EditAnywhere)
	float CrosshairY = 0.3333f; //Relative position of crosshair on screen

	UPROPERTY(EditAnywhere)
	float LookRange = 1000000.0f;
};