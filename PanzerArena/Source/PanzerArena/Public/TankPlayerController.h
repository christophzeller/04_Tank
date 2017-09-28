// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include <Tank.h>

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "TankPlayerController.generated.h"

/**
 * 
 */
UCLASS()
class PANZERARENA_API ATankPlayerController : public APlayerController
{
	GENERATED_BODY()
	
public:
	ATank* GetControlledTank() const;
	virtual void Tick(float DeltaTime) override;

	UPROPERTY(EditAnywhere)
	float CrosshairXLocation = 0.5f;
	
	UPROPERTY(EditAnywhere)
	float CrosshairYLocation = 0.3333f;

protected:
	virtual void BeginPlay() override;

private:
	void AimAtAimpoint();
	bool GetSightRayHitLocation(FVector& OutHitLocation) const;
	bool GetLookDirection(const FVector2D& ScreenLocation, FVector& OutLookDirection) const;
	
};
