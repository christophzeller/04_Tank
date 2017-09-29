// Fill out your copyright notice in the Description page of Project Settings.

#include "TankBarrelComponent.h"
#include <Engine/World.h>

void UTankBarrelComponent::Elevate(float RelativeSpeed)
{
	auto ElevationChange = FMath::Clamp<float>(RelativeSpeed, -1., 1.) * MaxDegreesPerSecond * GetWorld()->DeltaTimeSeconds;
	auto NewElevation = FMath::Clamp<float>(RelativeRotation.Pitch + ElevationChange, MinElevationDegrees, MaxElevationDegrees);

	SetRelativeRotation(FRotator(NewElevation, 0., 0.));
}