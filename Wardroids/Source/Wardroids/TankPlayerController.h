// Fill out your copyright notice in the Description page of Project Settings.

#pragma once


#include "Tank.h"
#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "TankPlayerController.generated.h" //Must be last

/**
 * 
 */
UCLASS()
class WARDROIDS_API ATankPlayerController : public APlayerController
{
	GENERATED_BODY()

public:
	virtual void BeginPlay() override;
	virtual void Tick(float DeltaTime) override;

	void AimTowardsCrosshair();
	bool GetSightRayHitLocation(FVector& HitLocation) const;
	bool GetLookDirection(FVector2D ScreenLocation, FVector& WorldDirection) const;

	ATank* Tank = nullptr;
	ATank* GetControlledTank() const;

	UPROPERTY(EditAnywhere)
	float CrosshairX = 0.5f;
	
	UPROPERTY(EditAnywhere)
	float CrosshairY = 0.3333f;
};