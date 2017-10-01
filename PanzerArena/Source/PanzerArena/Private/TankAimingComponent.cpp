// Fill out your copyright notice in the Description page of Project Settings.

#include "TankAimingComponent.h"
#include <GameFramework/Actor.h>
#include <Kismet/GameplayStatics.h>

#include <Engine/StaticMeshSocket.h>
#include <Engine/World.h>

#include <TankBarrelComponent.h>
#include <TankTurretComponent.h>
#include <Shell.h>

// Sets default values for this component's properties
UTankAimingComponent::UTankAimingComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;
	// ...
}


// Called when the game starts
void UTankAimingComponent::BeginPlay()
{
	Super::BeginPlay();
	LastFireTime = FPlatformTime::Seconds();
}


// Called every frame
void UTankAimingComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);
	bool isReloaded = (FPlatformTime::Seconds() - LastFireTime) > ReloadTime;
	if (!isReloaded)
	{
		FiringState = EFiringState::Reloading;
	}
	else
	{
		//UE_LOG(LogTemp, Warning, TEXT("IsBarrelMoving(): %s"), IsBarrelMoving() ? TEXT("TRUE") : TEXT("FALSE"));
		if (IsBarrelMoving())
		{
			FiringState = EFiringState::Aiming;
		}
		else
		{
			FiringState = EFiringState::Locked;
		}
	}
	
}

void UTankAimingComponent::AimAt(const FVector& TargetLocation)
{
	if (!ensure(Barrel && Turret))
	{
		return;
	}

	auto BarrelLocation = Barrel->GetSocketLocation(FName("Muzzle"));
	FVector ShellVelocity{};

	//UE_LOG(LogTemp, Warning, TEXT("MuzzleLocation: %s"), (*BarrelLocation.ToString()));
	bool bHasFiringSolution = UGameplayStatics::SuggestProjectileVelocity(
		this,
		ShellVelocity,
		BarrelLocation,
		TargetLocation,
		LaunchSpeed,
		false,
		0.f,
		0.f,
		ESuggestProjVelocityTraceOption::DoNotTrace
	);
	
	if (bHasFiringSolution)
	{
		AimDirection = ShellVelocity.GetSafeNormal();
		auto TankName = GetOwner()->GetName();

		MoveBarrel(AimDirection);
		MoveTurret(AimDirection);
	}

}

void UTankAimingComponent::SetBarrelReference(UTankBarrelComponent* Barrel)
{
	this->Barrel = Barrel;
}

void UTankAimingComponent::SetTurretReference(UTankTurretComponent* Turret)
{
	this->Turret = Turret;
}

void UTankAimingComponent::MoveBarrel(const FVector& AimDirection)
{
	auto BarrelRotator = Barrel->GetForwardVector().Rotation();
	auto AimRotator = AimDirection.Rotation();

	auto DeltaRotator = AimRotator - BarrelRotator;

	Barrel->Elevate(DeltaRotator.Pitch);
	//UE_LOG(LogTemp, Warning, TEXT("DeltaRotator: %s "), *(DeltaRotator.ToString()));

	// takes target vector
	// rotates the turret on the xy plane until desired azimuth is achieved
	// rotates the barrel around the x axis until desired elevation is achieved
	// 
}

void UTankAimingComponent::MoveTurret(const FVector& AimDirection)
{
	auto TurretRotator = Turret->GetForwardVector().Rotation();
	auto AimRotator = AimDirection.Rotation();

	auto DeltaRotator = AimRotator - TurretRotator;

	Turret->Rotate(DeltaRotator.Yaw);
}


void UTankAimingComponent::Initialize(UTankBarrelComponent* Barrel, UTankTurretComponent* Turret)
{
	SetBarrelReference(Barrel);
	SetTurretReference(Turret);
}

void UTankAimingComponent::Fire()
{
	if (!ensure(Barrel))
	{
		return;
	}

	if (FiringState != EFiringState::Reloading)
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

bool UTankAimingComponent::IsBarrelMoving() const
{
	if (!ensure(Barrel))
	{
		return false;
	}

	auto BarrelForward = Barrel->GetForwardVector().GetSafeNormal();

	return !BarrelForward.Equals(AimDirection, 0.01f);
}