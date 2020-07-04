// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/StaticMeshComponent.h"
#include "TankBarrelComponent.generated.h"

/**
 * 
 */
UCLASS( meta = (BlueprintSpawnableComponent) )
class WARDROIDS_API UTankBarrelComponent : public UStaticMeshComponent
{
	GENERATED_BODY()

public:

	void Elevate( float DegreesPerSecond );
	
private:

	UPROPERTY( EditAnywhere, Category = Actions)
	float MaxDegreesPerSecond = 20.0f;

	UPROPERTY( EditAnywhere, Category = Actions )
	float MaxElevationDegrees = 40.0f;

	UPROPERTY( EditAnywhere, Category = Actions )
	float MinElevationDegrees = 0.0f;
};
