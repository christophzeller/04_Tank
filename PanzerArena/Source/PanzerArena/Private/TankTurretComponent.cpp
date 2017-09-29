// Fill out your copyright notice in the Description page of Project Settings.

#include "TankTurretComponent.h"
#include <Engine/World.h>

void UTankTurretComponent::Rotate(float RelativeSpeed)
{
	auto RotationChange = FMath::Clamp<float>(RelativeSpeed, -1., 1.) * MaxDegreesPerSecond * GetWorld()->DeltaTimeSeconds;
	auto NewRotation = RelativeRotation.Yaw + RotationChange; //FMath::Clamp<float>(RelativeRotation.Yaw + RotationChange, -360.f, 360.f);

	SetRelativeRotation(FRotator(0., NewRotation, 0.));
}