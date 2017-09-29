// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Shell.generated.h"

class UProjectileMovementComponent;

UCLASS()
class PANZERARENA_API AShell : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AShell();
	void Launch(float Speed);

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	
private:
	UProjectileMovementComponent* ProjectileMovementComponent = nullptr;
	
};
