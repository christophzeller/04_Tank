// Fill out your copyright notice in the Description page of Project Settings.

#include "TankNavMovementComponent.h"
#include "TankTrackComponent.h"

void UTankNavMovementComponent::Initialize(UTankTrackComponent* LeftTrack, UTankTrackComponent* RightTrack)
{
	this->LeftTrack = LeftTrack;
	this->RightTrack = RightTrack;
}

void UTankNavMovementComponent::IntendMoveForward(float Throttle)
{
	if (!ensure(LeftTrack && RightTrack))
	{
		return;
	}
	FMath::Clamp(Throttle, -1.f, 1.f);
	LeftTrack->SetThrottle(Throttle);
	RightTrack->SetThrottle(Throttle);
}


void UTankNavMovementComponent::IntendTurn(float Throttle)
{
	if (!ensure(LeftTrack && RightTrack))
	{
		return;
	}
	FMath::Clamp(Throttle, -1.f, 1.f);
	LeftTrack->SetThrottle(Throttle);
	RightTrack->SetThrottle(-Throttle);
}

void UTankNavMovementComponent::RequestDirectMove(const FVector& MoveVelocity, bool bForceMaxSpeed)
{
	//Super::RequestDirectMove(MoveVelocity, bForceMaxSpeed);
	//UE_LOG(LogTemp, Warning, TEXT("%s moving to %s"), *GetOwner()->GetName(), *MoveVelocity.ToString());

	auto NewForward = MoveVelocity.GetSafeNormal();
	auto TankForward = GetOwner()->GetActorForwardVector().GetSafeNormal();
	
	auto ForwardThrottle = FVector::DotProduct(TankForward, NewForward);
	auto TurnThrottle = FVector::CrossProduct(TankForward, NewForward).Z;

	IntendMoveForward(ForwardThrottle);
	IntendTurn(TurnThrottle);
}