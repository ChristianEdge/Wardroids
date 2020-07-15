// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/StaticMeshComponent.h"
#include "TankTrackComponent.generated.h"

/**
 * 
 */
UCLASS( meta = ( BlueprintSpawnableComponent ) )
class WARDROIDS_API UTankTrackComponent : public UStaticMeshComponent
{
	GENERATED_BODY()
	
public:

	UFUNCTION( BlueprintCallable )
	void SetThrottle( float NewThrottle );
};
