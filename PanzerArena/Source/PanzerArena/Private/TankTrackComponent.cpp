// Fill out your copyright notice in the Description page of Project Settings.

#include "TankTrackComponent.h"

UTankTrackComponent::UTankTrackComponent()
{
	PrimaryComponentTick.bCanEverTick = true;
}

void UTankTrackComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	auto SlippageSpeed = FVector::DotProduct(GetRightVector(), GetComponentVelocity());
	auto SlippageForce = (SlippageSpeed / DeltaTime) * GetRightVector();
	
	auto TankRoot = Cast<UPrimitiveComponent>(GetOwner()->GetRootComponent());
	auto CorrectionForce = (TankRoot->GetMass() * -SlippageForce) / 2.f;

	TankRoot->AddForce(CorrectionForce);
}

void UTankTrackComponent::SetThrottle(float Throttle)
{
	//float ClampedThrottle = 

	auto ThrottleForce = GetForwardVector() * Throttle * MaxDrivingForce;
	auto ForceLocation = GetComponentLocation();

	auto TankRoot = Cast<UPrimitiveComponent>(GetOwner()->GetRootComponent());
	TankRoot->AddForceAtLocation(ThrottleForce, ForceLocation);
	//UE_LOG(LogTemp, Warning, TEXT("SetThrottle %f"), Throttle);
}
