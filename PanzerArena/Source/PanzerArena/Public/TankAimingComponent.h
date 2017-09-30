// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"

#include "TankAimingComponent.generated.h"

UENUM()
enum class EFiringState : uint8
{
	Reloading, 
	Aiming, 
	Locked
};

class UTankBarrelComponent;
class UTankTurretComponent;

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class PANZERARENA_API UTankAimingComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UTankAimingComponent();

	void SetBarrelReference(UTankBarrelComponent* Barrel);
	void SetTurretReference(UTankTurretComponent* Turret);

protected:
	// Called when the game starts
	virtual void BeginPlay() override;
	void MoveBarrel(const FVector& AimDirection);
	void MoveTurret(const FVector& AimDirection);

	UPROPERTY(BlueprintReadOnly, Category = "State")
	EFiringState FiringState = EFiringState::Reloading;

public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

	virtual void AimAt(const FVector& TargetLocation, float LaunchSpeed);

private:
	UTankBarrelComponent* Barrel = nullptr;
	UTankTurretComponent* Turret = nullptr;

	
	
};
