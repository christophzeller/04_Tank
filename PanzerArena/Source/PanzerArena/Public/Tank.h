// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include "Templates/SubclassOf.h"

#include "Tank.generated.h"
class UTankBarrelComponent;
class UTankTurretComponent;
class UTankAimingComponent;
class UTankNavMovementComponent;
class AShell;

UCLASS()
class PANZERARENA_API ATank : public APawn
{
	GENERATED_BODY()

public:
	// Sets default values for this pawn's properties
	ATank();
	void AimAt(FVector TargetLocation);

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	UFUNCTION(BlueprintCallable, Category = Setup)
	void SetBarrelReference(UTankBarrelComponent* Barrel);

	UFUNCTION(BlueprintCallable, Category = Setup)
	void SetTurretReference(UTankTurretComponent* Turret);

	UFUNCTION(BlueprintCallable, Category = Input)
	void Fire();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	UTankAimingComponent* TankAimingComponent = nullptr;

	UPROPERTY(BlueprintReadonly, Category = Setup)
	UTankNavMovementComponent* TankMovementComponent = nullptr;

private:
	double LastFireTime = 0.f;

	UPROPERTY(EditDefaultsOnly, Category = Firing)
	float ReloadTime = 3.f;

	UPROPERTY(EditDefaultsOnly, Category = Firing)
	float LaunchSpeed = 100000.f;
	
	// used to spawn shells
	UPROPERTY(EditAnywhere, Category = Setup)
	TSubclassOf<AShell> ShellBlueprint;

	UTankBarrelComponent* Barrel = nullptr;
};
