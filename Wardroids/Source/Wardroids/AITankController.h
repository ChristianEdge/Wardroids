// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "AIController.h"
#include "CoreMinimal.h"
#include "AITankController.generated.h" //Must be last

class ATank;

UCLASS()
class WARDROIDS_API AAITankController : public AAIController
{
	GENERATED_BODY()

public:
	virtual void BeginPlay() override;
	virtual void Tick( float DeltaTime ) override;

	void AimAtTarget( FVector HitLocation );

	ATank* GetControlledTank() const;
	ATank* GetPlayerTank() const;
};
