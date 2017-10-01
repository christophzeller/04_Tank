// Fill out your copyright notice in the Description page of Project Settings.

#include "TankAIController.h"
#include <Engine/World.h>
#include <TankPlayerController.h>
#include <Tank.h>

void ATankAIController::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	
	PlayerTank = Cast<ATank>(GetWorld()->GetFirstPlayerController()->GetPawn());

	if (ensure(PlayerTank))
	{
		MoveToActor(PlayerTank, StandOffDistance);

		ControlledTank->AimAt(PlayerTank->GetActorLocation());
		ControlledTank->Fire();
	}
}

void ATankAIController::BeginPlay()
{
	Super::BeginPlay();
	ControlledTank = Cast<ATank>(GetPawn());
}