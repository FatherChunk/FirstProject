// Fill out your copyright notice in the Description page of Project Settings.


#include "Pickup.h"
#include "Main.h"

APickup::APickup()
{
	CoinCount = 1;
}

void APickup::OnOverlapBegin(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	Super::OnOverlapBegin(OverlappedComponent, OtherActor, OtherComp, OtherBodyIndex, bFromSweep, SweepResult);

	UE_LOG(LogTemp, Warning, TEXT("Pickup::OnOverlap Begin"));

	if (OtherActor)
	{
		AMain* Main = Cast<AMain>(OtherActor); // checks if another actor
		if (Main)
		{
			Main->IncrementCoins(CoinCount); // calls to increase coin count function in main
			Main->PickupLocations.Add(GetActorLocation());

			Destroy();
		}
	}
}

void APickup::OnOverlapEnd(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{
	Super::OnOverlapEnd(OverlappedComponent, OtherActor, OtherComp, OtherBodyIndex);

	UE_LOG(LogTemp, Warning, TEXT("Pickup::OnOverlap end"));
}
