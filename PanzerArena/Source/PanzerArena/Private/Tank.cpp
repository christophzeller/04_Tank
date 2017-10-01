// Fill out your copyright notice in the Description page of Project Settings.

#include "Tank.h"
#include <TankBarrelComponent.h>
#include <TankTurretComponent.h>
#include <TankAimingComponent.h>
#include <TankNavMovementComponent.h>
#include <Engine/World.h>
#include <Engine/StaticMeshSocket.h>
#include <Shell.h>

// Sets default values
ATank::ATank()
{
 	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;
}

void ATank::BeginPlay()
{
	Super::BeginPlay();
}

// Called to bind functionality to input
void ATank::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);
}

void ATank::AimAt(FVector TargetLocation)
{
	if (ensure(TankAimingComponent))
		TankAimingComponent->AimAt(TargetLocation, LaunchSpeed);

}

void ATank::Fire()
{
	bool isReloaded = (FPlatformTime::Seconds() - LastFireTime) > ReloadTime;

	if (ensure(Barrel) && isReloaded)
	{
		// spawn projectile at muzzle socket
		auto Shell = GetWorld()->SpawnActor<AShell>(
			ShellBlueprint,
			Barrel->GetSocketLocation(FName("Muzzle")),
			Barrel->GetSocketRotation(FName("Muzzle"))
			);

		LastFireTime = FPlatformTime::Seconds();

		if (ensure(Shell))
		{
			Shell->Launch(LaunchSpeed);
		}
		else
		{
			UE_LOG(LogTemp, Warning, TEXT("%f failed to spawn BOOM :("), GetWorld()->GetTimeSeconds());
		}
	}
}