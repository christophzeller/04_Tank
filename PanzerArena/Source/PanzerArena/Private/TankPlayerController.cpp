// Fill out your copyright notice in the Description page of Project Settings.

#include "TankPlayerController.h"
#include <Engine/World.h>
#include <Tank.h>
#include <TankAimingComponent.h>

void ATankPlayerController::BeginPlay()
{
	Super::BeginPlay();

	PrimaryActorTick.bCanEverTick = true;
	AimingComponent = GetPawn()->FindComponentByClass<UTankAimingComponent>();
	if (ensure(AimingComponent))
	{
		FoundAimingComponent(AimingComponent);
	}
	else
	{
		UE_LOG(LogTemp, Error, TEXT("No AimingComponent found on %s"), *GetPawn()->GetName());
	}
}

// Called every frame
void ATankPlayerController::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	// will produce tons of spam because unreal engine bug
	//UE_LOG(LogTemp, Warning, TEXT("ATankPlayerController::Tick")); 
	// aim at aimpoint
	AimAtAimpoint();
}

void ATankPlayerController::AimAtAimpoint()
{
	if (!GetPawn()) { return; }

	FVector HitLocation {};
	AimingComponent = GetPawn()->FindComponentByClass<UTankAimingComponent>();

	if (!ensure(AimingComponent)) 
	{
		return;
	}

	if (GetSightRayHitLocation(HitLocation))
	{
		AimingComponent->AimAt(HitLocation);
	}
}

bool ATankPlayerController::GetSightRayHitLocation(FVector& OutHitLocation) const
{
	// get UI widget point
	// convert point location from screen space to world space
	// cast ray from tank through widget dot location
	// LineTraceSingleByChannel
	// check for intersection with stuff
	// return

	int32 ViewportSizeX, ViewportSizeY;
	GetViewportSize(ViewportSizeX, ViewportSizeY);

	FVector2D ScreenLocation{ ViewportSizeX * CrosshairXLocation, ViewportSizeY * CrosshairYLocation };

	FVector LookDirection{};
	if (GetLookDirection(ScreenLocation, LookDirection))
	{
		return GetLookVectorHitLocation(OutHitLocation, LookDirection);
	}

	return false;
}

bool ATankPlayerController::GetLookDirection(const FVector2D& ScreenLocation, FVector& OutLookDirection) const
{
	FVector Location{};

	return DeprojectScreenPositionToWorld(ScreenLocation.X, ScreenLocation.Y, Location, OutLookDirection);
}

bool ATankPlayerController::GetLookVectorHitLocation(FVector& OutHitLocation, const FVector& LookDirection) const
{
	FHitResult HitResult{};
	FVector CameraLocation;

	CameraLocation = PlayerCameraManager->GetCameraLocation();

	bool hasHit = GetWorld()->LineTraceSingleByChannel(
		HitResult, 
		CameraLocation, 
		CameraLocation + LookDirection * LineTraceRange, 
		ECollisionChannel::ECC_Visibility
	);
	
	OutHitLocation = HitResult.Location;

	return hasHit;
}