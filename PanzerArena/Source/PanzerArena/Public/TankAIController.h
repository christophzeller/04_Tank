// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AIController.h"
#include "TankAIController.generated.h"

class ATank;

/**
 * 
 */
UCLASS()
class PANZERARENA_API ATankAIController : public AAIController
{
	GENERATED_BODY()

public:
	virtual void Tick(float DeltaTime) override;
	
private:
	//UPROPERTY(BlueprintAssignable)
	float StandOffDistance = 3000.f;
	ATank* ControlledTank;
	ATank* PlayerTank;

protected:
	virtual void BeginPlay() override;
	
};
