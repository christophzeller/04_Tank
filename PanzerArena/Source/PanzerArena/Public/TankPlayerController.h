// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "TankPlayerController.generated.h"

class UTankAimingComponent;

/**
 * 
 */
UCLASS()
class PANZERARENA_API ATankPlayerController : public APlayerController
{
	GENERATED_BODY()
	
public:
	UFUNCTION(BlueprintCallable, Category = "Setup")

	virtual void Tick(float DeltaTime) override;

	UPROPERTY(EditDefaultsOnly)
	float CrosshairXLocation = 0.5f;
	
	UPROPERTY(EditDefaultsOnly)
	float CrosshairYLocation = 0.3333f;

protected:
	UFUNCTION(BlueprintImplementableEvent, Category = "Setup")
	void FoundAimingComponent(UTankAimingComponent* AimCompRef);
	UTankAimingComponent* AimingComponent = nullptr;

	virtual void BeginPlay() override;

private:
	void AimAtAimpoint();
	bool GetSightRayHitLocation(FVector& OutHitLocation) const;
	bool GetLookDirection(const FVector2D& ScreenLocation, FVector& OutLookDirection) const;
	bool GetLookVectorHitLocation(FVector& OutHitLocation, const FVector& LookDirection) const;

	UPROPERTY(EditDefaultsOnly)
	float LineTraceRange = 1000000.f;
	
};
