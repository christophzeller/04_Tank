// Fill out your copyright notice in the Description page of Project Settings.

#include "Shell.h"
#include <Components/StaticMeshComponent.h>
#include <GameFramework/ProjectileMovementComponent.h>
#include <Particles/ParticleSystemComponent.h>

// Sets default values
AShell::AShell()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	CollisionMesh = CreateDefaultSubobject<UStaticMeshComponent>(FName("Collision Mesh"));
	CollisionMesh->SetNotifyRigidBodyCollision(true);
	CollisionMesh->SetVisibility(true);

	SetRootComponent(CollisionMesh);

	ProjectileMovementComponent = CreateDefaultSubobject<UProjectileMovementComponent>(FName("ProjectileMovementComponent"));
	ProjectileMovementComponent->bAutoActivate = false;

	LaunchBlast = CreateDefaultSubobject<UParticleSystemComponent>(FName("Launch Blast"));
	LaunchBlast->AttachTo(RootComponent);
	
	
}

// Called when the game starts or when spawned
void AShell::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AShell::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void AShell::Launch(float Speed)
{
	//UE_LOG(LogTemp, Warning, TEXT("%f BOOM %f"), GetWorld()->GetTimeSeconds(), Speed);
	ProjectileMovementComponent->SetVelocityInLocalSpace(FVector::ForwardVector * Speed);
	ProjectileMovementComponent->Activate();
}