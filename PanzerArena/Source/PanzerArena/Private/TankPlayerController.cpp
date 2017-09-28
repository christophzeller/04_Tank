// Fill out your copyright notice in the Description page of Project Settings.

#include "TankPlayerController.h"


ATank* ATankPlayerController::GetControlledTank() const
{
	return Cast<ATank>(GetPawn());
}

void ATankPlayerController::BeginPlay()
{
	Super::BeginPlay();
	UE_LOG(LogTemp, Warning, TEXT("TankPlayerController says hello."));
	auto Tank = GetControlledTank();

	if (Tank)
	{
		UE_LOG(LogTemp, Warning, TEXT("TankPlayerController has %s attached."), *(Tank->GetName()));
	}
	else
	{
		UE_LOG(LogTemp, Error, TEXT("No Tank instance attached to TankPlayerController"));
	}
}
