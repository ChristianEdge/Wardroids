// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include "TurretAimingComponent.h"
#include "Tank.generated.h" //Must be the final include

UCLASS()
class WARDROIDS_API ATank : public APawn
{
	GENERATED_BODY()

public:
	ATank();

	void AimAtLocation( FVector HitLocation );

	UFUNCTION( BlueprintCallable, Category = Setup )
	void SetBarrelReference( UStaticMeshComponent* NewBarrel );

	UPROPERTY( EditAnywhere, Category = Attack )
	float ProjectileLaunchVelocity = 100000.0f;

protected:
	UTurretAimingComponent* Turret = nullptr;

private:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	// Called every frame
	virtual void Tick( float DeltaTime ) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent( class UInputComponent* PlayerInputComponent ) override;
};
