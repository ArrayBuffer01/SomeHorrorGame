// Fill out your copyright notice in the Description page of Project Settings.

#include "Items/Flashlight.h"
#include "Components/SpotLightComponent.h"

AFlashlight::AFlashlight()
{
	FlashlightMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("FlashlightMesh"));
	FlashlightMesh->SetupAttachment(RootComponent);

	Spotlight = CreateDefaultSubobject<USpotLightComponent>(TEXT("Spotlight"));
	Spotlight->SetupAttachment(FlashlightMesh);

	bIsOn = false;
}

void AFlashlight::ToggleFlashlight()
{
	bIsOn = !bIsOn;

	if (Spotlight)
	{
		Spotlight->SetVisibility(bIsOn);
	}


	OnStateChange(bIsOn);
	StateChanged.Broadcast(bIsOn);
}

void AFlashlight::OnConstruction(const FTransform& Transform)
{
	Super::OnConstruction(Transform);

	if (Spotlight)
	{
		Spotlight->SetVisibility(bIsOn);
	}
}

void AFlashlight::PickupItem_Implementation()
{
	FlashlightMesh->SetSimulatePhysics(false);
}

void AFlashlight::ReleaseItem_Implementation()
{
	FlashlightMesh->SetSimulatePhysics(true);
}

void AFlashlight::Use_Implementation(AActor* User)
{
	ToggleFlashlight();
}