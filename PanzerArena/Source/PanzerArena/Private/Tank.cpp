// Fill out your copyright notice in the Description page of Project Settings.

#include "Tank.h"
#include <TankBarrelComponent.h>
#include <TankTurretComponent.h>
#include <TankAimingComponent.h>
#include <Engine/World.h>
#include <Engine/StaticMeshSocket.h>
#include <Shell.h>

// Sets default values
ATank::ATank()
{
 	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;

	TankAimingComponent = CreateDefaultSubobject<UTankAimingComponent>(FName("AimingComponent"));
}

// Called when the game starts or when spawned
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
	TankAimingComponent->AimAt(TargetLocation, LaunchSpeed);
	//auto ThisTankName = GetName();
	//UE_LOG(LogTemp, Warning, TEXT("%s aiming at %s"), *ThisTankName, *(TargetLocation.ToString()));
}

void ATank::SetBarrelReference(UTankBarrelComponent* Barrel)
{
	TankAimingComponent->SetBarrelReference(Barrel);
	this->Barrel = Barrel;
}

void ATank::SetTurretReference(UTankTurretComponent* Turret)
{
	TankAimingComponent->SetTurretReference(Turret);
}

void ATank::Fire()
{
	bool isReloaded = (FPlatformTime::Seconds() - LastFireTime) > ReloadTime;

	if (Barrel && isReloaded)
	{
		// spawn projectile at muzzle socket
		auto Shell = GetWorld()->SpawnActor<AShell>(
			ShellBlueprint,
			Barrel->GetSocketLocation(FName("Muzzle")),
			Barrel->GetSocketRotation(FName("Muzzle"))
			);

		LastFireTime = FPlatformTime::Seconds();

		if (Shell)
		{
			Shell->Launch(LaunchSpeed);
		}
		else
		{
			UE_LOG(LogTemp, Warning, TEXT("%f failed to spawn BOOM :("), GetWorld()->GetTimeSeconds());
		}
	}
}