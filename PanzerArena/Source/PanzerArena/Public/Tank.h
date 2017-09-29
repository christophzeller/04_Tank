// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"

#include "Tank.generated.h"
class UTankBarrelComponent;
class UTankTurretComponent;
class UTankAimingComponent;

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
	void SetTurretReference(UTankTurretComponent* Barrel);

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	UTankAimingComponent* TankAimingComponent = nullptr;

private:
	UPROPERTY(EditAnywhere, Category = Firing)
	float LaunchSpeed = 100000.f;
	
	
};
