// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/StaticMeshComponent.h"
#include "TurretComponent.generated.h"


UCLASS( meta = (BlueprintSpawnableComponent) )
class WARDROIDS_API UTurretComponent : public UStaticMeshComponent
{
	GENERATED_BODY()

public:
	
	//Relative speed between -1 (move down) and +1 (move up)
	void Rotate( float RelativeSpeed );

private:

	UPROPERTY( EditAnywhere, Category = Actions)
	float MaxDegreesPerSecond = 8.0f;

};
