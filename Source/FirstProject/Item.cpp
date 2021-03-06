// Fill out your copyright notice in the Description page of Project Settings.


#include "Item.h"
#include "Components/SphereComponent.h"
#include "Components/StaticMeshComponent.h"
#include "Particles/ParticleSystemComponent.h"
#include "Kismet/GameplayStatics.h"
#include "Engine/World.h"
#include "Sound/SoundCue.h"

// Sets default values
AItem::AItem()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	CollisionVolume = CreateDefaultSubobject<USphereComponent>(TEXT("CollisionVolume")); // Creates a sphere collision volume
	RootComponent = CollisionVolume; //Sets the collision volume as the root component

	Mesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Mesh")); //intitialises the mesh in the BP
	Mesh->SetupAttachment(GetRootComponent()); // Attaches to the root

	IdleParticlesComponent = CreateDefaultSubobject<UParticleSystemComponent>(TEXT("Particles")); //initialises the particle system
	IdleParticlesComponent->SetupAttachment(GetRootComponent()); // Attaches to root
	
	bRotate = false;

	RotationRate = 45.f;

}

// Called when the game starts or when spawned
void AItem::BeginPlay()
{
	Super::BeginPlay();

	CollisionVolume->OnComponentBeginOverlap.AddDynamic(this, &AItem::OnOverlapBegin); //creates functionality for starting overlap
	CollisionVolume->OnComponentEndOverlap.AddDynamic(this, &AItem::OnOverlapEnd); //creates functionality for ending overlap
	
}

// Called every frame
void AItem::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if (bRotate)
	{
		FRotator Rotation = GetActorRotation(); // Get current rotation 
		Rotation.Yaw += DeltaTime * RotationRate; // Setting Rotation in the Z axis (Yaw) equal to time * rate for consistent rotation rate
		SetActorRotation(Rotation); // Set the rotation by passing in the rotation rate set in the line above
	}

}

void AItem::OnOverlapBegin(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	UE_LOG(LogTemp, Warning, TEXT("Super::OnOverlap Begin"));

	if (OverlapParticles)
	{
		UGameplayStatics::SpawnEmitterAtLocation(GetWorld(), OverlapParticles, GetActorLocation(), FRotator(0.f), true); // Spawns the particle emitter at the location of the actor
	}
	if (OverlapSound)
	{
		UGameplayStatics::PlaySound2D(this, OverlapSound);
	}
	
}

void AItem::OnOverlapEnd(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{
	UE_LOG(LogTemp, Warning, TEXT("Super::OnOverlap end"));
}

