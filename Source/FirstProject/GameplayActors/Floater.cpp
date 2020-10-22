// Fill out your copyright notice in the Description page of Project Settings.


#include "Floater.h"

// Sets default values
AFloater::AFloater()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	StaticMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("CustomStaticMesh"));

	InitialLocation = FVector(0.0f);
	PlacedLocation = FVector(0.0f);
	WorldOrigin = FVector(0.0f, 0.0f, 0.0f);

	InitialDirection = FVector(0.0f, 0.0f, 0.0f);

	bInitialiseFloaterLocations = false;
	bShouldFloat = false;

	InitialForce = FVector(2000000.f, 0.f, 0.f);
	InitialTorque = FVector(2000000.f, 0.f, 0.f);
}

// Called when the game starts or when spawned
void AFloater::BeginPlay()
{
	Super::BeginPlay();

	PlacedLocation = GetActorLocation();

	if (bInitialiseFloaterLocations)
	{
		SetActorLocation(InitialLocation);
	}

	//FVector InitialForce = FVector(2000000.f, 0.f, 0.f);

	StaticMesh->AddForce(InitialForce);
	StaticMesh->AddTorque(InitialTorque);

	//FHitResult HitResult;
	//FVector LocalOffset = FVector(200.f, 0.f, 0.f);
	//AddActorWorldOffset(LocalOffset, true, &HitResult);
	
}

// Called every frame
void AFloater::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if (bShouldFloat)
	{
		FHitResult HitResult;
		AddActorLocalOffset(InitialDirection, true, &HitResult);

		FVector HitLocation = HitResult.Location;

		//UE_LOG(LogTemp, Warning, TEXT("Hit Location: X = %f, Y = %f, Z = %f"), HitLocation.X, HitLocation.Y, HitLocation.Z);
	}

	//FRotator Rotation = FRotator(0.0f, 0.0f, 1.0f);
	
	//AddActorWorldRotation(Rotation);
}

