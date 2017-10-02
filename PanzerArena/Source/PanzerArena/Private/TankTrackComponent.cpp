// Fill out your copyright notice in the Description page of Project Settings.

#include "TankTrackComponent.h"
#include <Engine/World.h>

UTankTrackComponent::UTankTrackComponent()
{
}

void UTankTrackComponent::BeginPlay()
{
	OnComponentHit.AddDynamic(this, &UTankTrackComponent::OnHit);
}


void UTankTrackComponent::OnHit(UPrimitiveComponent* HitComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit)
{
	DriveTrack();
	NeutralizeSlippage();
	CurrentThrottle = 0.f;
}

void UTankTrackComponent::NeutralizeSlippage()
{
	auto DeltaTime = GetWorld()->GetDeltaSeconds();
	auto SlippageSpeed = FVector::DotProduct(GetRightVector(), GetComponentVelocity());
	auto SlippageForce = (SlippageSpeed / DeltaTime) * GetRightVector();

	auto TankRoot = Cast<UPrimitiveComponent>(GetOwner()->GetRootComponent());
	auto CorrectionForce = (TankRoot->GetMass() * -SlippageForce) / 2.f;

	TankRoot->AddForce(CorrectionForce);
}

void UTankTrackComponent::SetThrottle(float Throttle)
{
	CurrentThrottle = FMath::Clamp<float>(CurrentThrottle + Throttle, -1.f, 1.f);
}

void UTankTrackComponent::DriveTrack()
{
	auto ThrottleForce = GetForwardVector() * CurrentThrottle * MaxDrivingForce;
	auto ForceLocation = GetComponentLocation();

	auto TankRoot = Cast<UPrimitiveComponent>(GetOwner()->GetRootComponent());
	TankRoot->AddForceAtLocation(ThrottleForce, ForceLocation);
}