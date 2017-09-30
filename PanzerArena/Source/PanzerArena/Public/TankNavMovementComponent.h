// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/NavMovementComponent.h"
#include "TankNavMovementComponent.generated.h"

class UTankTrackComponent;

/**
 * 
 */
UCLASS( ClassGroup = (Custom), meta = (BlueprintSpawnableComponent) )
class PANZERARENA_API UTankNavMovementComponent : public UNavMovementComponent
{
	GENERATED_BODY()

public:
	UFUNCTION(BlueprintCallable, Category = Input)
	void Initialize(UTankTrackComponent* LeftTrack, UTankTrackComponent* RightTrack);
	//
	UFUNCTION(BlueprintCallable, Category = Input)
	void IntendMoveForward(float Throttle);

	UFUNCTION(BlueprintCallable, Category = Input)
	void IntendTurn(float Throttle);

	virtual void RequestDirectMove(const FVector& MoveVelocity, bool bForceMaxSpeed) override;

	//void SetTrackReferences(UTankTrackComponent* LeftTrack, UTankTrackComponent* RightTrack);
	
private:
	UTankTrackComponent* LeftTrack = nullptr;
	UTankTrackComponent* RightTrack = nullptr;
};
