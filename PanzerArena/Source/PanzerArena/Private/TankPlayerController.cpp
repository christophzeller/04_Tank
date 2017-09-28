// Fill out your copyright notice in the Description page of Project Settings.

#include "TankPlayerController.h"


ATank* ATankPlayerController::GetControlledTank() const
{
	return Cast<ATank>(GetPawn());
}

void ATankPlayerController::BeginPlay()
{
	Super::BeginPlay();

	PrimaryActorTick.bCanEverTick = true;

	UE_LOG(LogTemp, Warning, TEXT("TankPlayerController says hello."));
	auto Tank = GetControlledTank();

	if (Tank)
	{
		UE_LOG(LogTemp, Warning, TEXT("TankPlayerController has %s attached."), *(Tank->GetName()));
	}
	else
	{
		UE_LOG(LogTemp, Error, TEXT("No Tank instance attached to TankPlayerController"));
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
	if (!GetControlledTank()) { return;  }

	FVector HitLocation {};

	if (GetSightRayHitLocation(HitLocation))
	{
		// rotate turret there
	}
}

bool ATankPlayerController::GetSightRayHitLocation(FVector& OutHitLocation) const
{
	// get UI widget point
	// convert point location from screen space to world space
	// cast ray from tank through widget dot location
	// check for intersection with stuff
	// return

	int32 ViewportSizeX, ViewportSizeY;
	GetViewportSize(ViewportSizeX, ViewportSizeY);

	FVector2D ScreenLocation{ ViewportSizeX * CrosshairXLocation, ViewportSizeY * CrosshairYLocation };

	FVector LookDirection{};
	if (GetLookDirection(ScreenLocation, LookDirection))
	{
		UE_LOG(LogTemp, Warning, TEXT("LookDirection: %s"), *(LookDirection.ToString()));
		return false;
	}

	return false;
}

bool ATankPlayerController::GetLookDirection(const FVector2D& ScreenLocation, FVector& OutLookDirection) const
{
	FVector Location{};

	return DeprojectScreenPositionToWorld(ScreenLocation.X, ScreenLocation.Y, Location, OutLookDirection);
}