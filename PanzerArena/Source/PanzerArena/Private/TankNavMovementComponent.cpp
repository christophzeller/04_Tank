// Fill out your copyright notice in the Description page of Project Settings.

#include "TankNavMovementComponent.h"
#include "TankTrackComponent.h"

void UTankNavMovementComponent::Initialize(UTankTrackComponent* LeftTrack, UTankTrackComponent* RightTrack)
{
	if (!LeftTrack || !RightTrack)
	{
		return;
	}

	this->LeftTrack = LeftTrack;
	this->RightTrack = RightTrack;
}

void UTankNavMovementComponent::IntendMoveForward(float Throttle)
{
	FMath::Clamp(Throttle, -1.f, 1.f);
	LeftTrack->SetThrottle(Throttle);
	RightTrack->SetThrottle(Throttle);
}


void UTankNavMovementComponent::IntendTurn(float Throttle)
{
	UE_LOG(LogTemp, Warning, TEXT("IntendTurn: %f"), Throttle);
	FMath::Clamp(Throttle, -1.f, 1.f);
	LeftTrack->SetThrottle(Throttle);
	RightTrack->SetThrottle(-Throttle);
}