// Fill out your copyright notice in the Description page of Project Settings.

#include "TankPlayerController.h"
#include <Engine/World.h>
#include <Tank.h>
#include <TankAimingComponent.h>

ATank* ATankPlayerController::GetControlledTank() const
{
	return Cast<ATank>(GetPawn());
}

void ATankPlayerController::BeginPlay()
{
	Super::BeginPlay();

	PrimaryActorTick.bCanEverTick = true;
	auto AimingComponent = GetControlledTank()->FindComponentByClass<UTankAimingComponent>();
	if (ensure(AimingComponent))
	{
		FoundAimingComponent(AimingComponent);
	}
	else
	{
		UE_LOG(LogTemp, Error, TEXT("No AimingComponent found on %s"), *GetControlledTank()->GetName());
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
	if (GetControlledTank()) { return;  }

	FVector HitLocation {};

	if (GetSightRayHitLocation(HitLocation))
	{
		GetControlledTank()->AimAt(HitLocation);
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
		if (GetLookVectorHitLocation(OutHitLocation, LookDirection))
		{
			return true;
		}
		return false;
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