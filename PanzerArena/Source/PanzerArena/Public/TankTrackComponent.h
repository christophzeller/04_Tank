// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/StaticMeshComponent.h"
#include "TankTrackComponent.generated.h"

class UPrimitiveComponent;
class AActor;

/**
 * 
 */
UCLASS(meta = (BlueprintSpawnableComponent))
class PANZERARENA_API UTankTrackComponent : public UStaticMeshComponent
{
	GENERATED_BODY()
	
public:
	UTankTrackComponent();

	virtual void BeginPlay();

	UFUNCTION(BlueprintCallable, Category = "Input")
	void SetThrottle(float Throttle);

protected:
private:
	UFUNCTION()
	void OnHit(UPrimitiveComponent* HitComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit);

	void DriveTrack();
	void NeutralizeSlippage();

	UPROPERTY(EditDefaultsOnly, Category = "Setup")
	float MaxDrivingForce = 50000000.f;

	float CurrentThrottle = 0.f;
	
};
