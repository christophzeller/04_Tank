// Fill out your copyright notice in the Description page of Project Settings.

#include "TankAIController.h"
#include <Engine/World.h>
#include <TankPlayerController.h>
#include <Tank.h>

ATank* ATankAIController::GetControlledTank() const
{
	return Cast<ATank>(GetPawn());
}

ATank* ATankAIController::GetPlayerTank() const
{
	return Cast<ATank>(GetWorld()->GetFirstPlayerController()->GetPawn());
}

void ATankAIController::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	auto PlayerTank = GetPlayerTank();
	if (PlayerTank)
	{
		GetControlledTank()->AimAt(PlayerTank->GetActorLocation());
	}
}

void ATankAIController::BeginPlay()
{
	Super::BeginPlay();
	UE_LOG(LogTemp, Warning, TEXT("TankAIController says hello."));
	auto Tank = GetPlayerTank();

	if (Tank)
	{
		UE_LOG(LogTemp, Warning, TEXT("TankAIController found player tank: %s."), *(Tank->GetName()));
	}
	else
	{
		UE_LOG(LogTemp, Error, TEXT("TankAIController could not find player tank"));
	}
}