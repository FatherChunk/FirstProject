// Fill out your copyright notice in the Description page of Project Settings.


#include "MainPlayerController.h"
#include "Blueprint/UserWidget.h"

void AMainPlayerController::BeginPlay()
{
	Super::BeginPlay();

	if (HUDOverlayAsset)
	{
		HUDOverlay = CreateWidget<UUserWidget>(this, HUDOverlayAsset); // sets the HUD overlay
	}
	HUDOverlay->AddToViewport(); // adds overlay to the veiwport
	HUDOverlay->SetVisibility(ESlateVisibility::Visible); // set the visibility
}
