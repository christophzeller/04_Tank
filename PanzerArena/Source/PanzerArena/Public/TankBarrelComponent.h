// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/StaticMeshComponent.h"
#include "TankBarrelComponent.generated.h"

/**
 * Helpful information!
 */
UCLASS( meta=(BlueprintSpawnableComponent))
class PANZERARENA_API UTankBarrelComponent : public UStaticMeshComponent
{
	GENERATED_BODY()
	
public:
	void Elevate(float DegreesPerSecond);
	
private:
	UPROPERTY(EditAnywhere, Category=Setup)
	float MaxDegreesPerSecond = 20.f;

	UPROPERTY(EditAnywhere, Category = Setup)
	float MaxElevationDegrees = 15.0f;

	UPROPERTY(EditAnywhere, Category = Setup)
	float MinElevationDegrees = -1.5f;
};

