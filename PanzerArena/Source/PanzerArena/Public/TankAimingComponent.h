// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "Templates/SubclassOf.h"

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
class AShell;

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class PANZERARENA_API UTankAimingComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UTankAimingComponent();
	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;
	
	
	virtual void AimAt(const FVector& TargetLocation);

	void SetBarrelReference(UTankBarrelComponent* Barrel);
	void SetTurretReference(UTankTurretComponent* Turret);

	UFUNCTION(BlueprintCallable)
	void Initialize(UTankBarrelComponent* Barrel, UTankTurretComponent* Turret);

	UFUNCTION(BlueprintCallable)
	void Fire();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;
	void MoveBarrel(const FVector& AimDirection);
	void MoveTurret(const FVector& AimDirection);

	UPROPERTY(BlueprintReadOnly, Category = "State")
	EFiringState FiringState = EFiringState::Reloading;


private:
	UTankBarrelComponent* Barrel = nullptr;
	UTankTurretComponent* Turret = nullptr;

	UPROPERTY(EditDefaultsOnly, Category = "Firing")
	float LaunchSpeed = 8000.f;

	double LastFireTime = 0.f;

	UPROPERTY(EditDefaultsOnly, Category = "Firing")
		float ReloadTime = 3.f;

	// used to spawn shells
	UPROPERTY(EditAnywhere, Category = "Setup")
		TSubclassOf<AShell> ShellBlueprint;
};
