// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include "Templates/SubclassOf.h"

#include "Tank.generated.h"
class UTankBarrelComponent;
class AShell;

UCLASS()
class PANZERARENA_API ATank : public APawn
{
	GENERATED_BODY()

public:
	// Sets default values for this pawn's properties
	ATank();

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	UFUNCTION(BlueprintCallable, Category = "Input")
	void Fire();

protected:
	virtual void BeginPlay() override;

private:
	double LastFireTime = 0.f;

	UPROPERTY(EditDefaultsOnly, Category = "Firing")
	float ReloadTime = 3.f;
	
	// used to spawn shells
	UPROPERTY(EditAnywhere, Category = "Setup")
	TSubclassOf<AShell> ShellBlueprint;

	UTankBarrelComponent* Barrel = nullptr;
};
