// Fill out your copyright notice in the Description page of Project Settings.

#include "TankAimingComponent.h"
#include <GameFramework/Actor.h>
#include <Kismet/GameplayStatics.h>
#include <Engine/World.h>

#include <TankBarrelComponent.h>
#include <TankTurretComponent.h>

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

	// ...
	
}


// Called every frame
void UTankAimingComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
	
}

void UTankAimingComponent::AimAt(const FVector& TargetLocation, float LaunchSpeed)
{
	if (!Barrel || !Turret)
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
		auto AimDirection = ShellVelocity.GetSafeNormal();
		auto TankName = GetOwner()->GetName();

		//UE_LOG(LogTemp, Warning, TEXT("%s aiming at %s from %s at %f"), *(GetOwner()->GetName()), *(TargetLocation.ToString()), *(BarrelLocation.ToString()), LaunchSpeed);
		UE_LOG(LogTemp, Warning, TEXT("%s aiming in direction: %s"), *(TankName), *(AimDirection.ToString()));

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