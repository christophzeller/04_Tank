// Fill out your copyright notice in the Description page of Project Settings.

#include "TankTrackComponent.h"

void UTankTrackComponent::SetThrottle(float Throttle)
{
	//float ClampedThrottle = 

	auto ThrottleForce = GetForwardVector() * Throttle * MaxDrivingForce;
	auto ForceLocation = GetComponentLocation();

	auto TankRoot = Cast<UPrimitiveComponent>(GetOwner()->GetRootComponent());
	TankRoot->AddForceAtLocation(ThrottleForce, ForceLocation);
	//UE_LOG(LogTemp, Warning, TEXT("SetThrottle %f"), Throttle);
}
