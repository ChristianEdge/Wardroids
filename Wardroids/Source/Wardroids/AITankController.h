// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Tank.h"
#include "AIController.h"
#include "CoreMinimal.h"
#include "AITankController.generated.h" //Must be last

/**
 * 
 */
UCLASS()
class WARDROIDS_API AAITankController : public AAIController
{
	GENERATED_BODY()

public:
	virtual void BeginPlay() override;
	virtual void Tick(float DeltaTime) override;

	void AimAtTarget(ATank* Target);

	ATank* Tank = nullptr;
	ATank* GetControlledTank() const;
	ATank* GetPlayerTank() const;

	ATank* PlayerTank = nullptr;
};
