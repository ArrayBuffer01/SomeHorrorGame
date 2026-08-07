// Fill out your copyright notice in the Description page of Project Settings.


#include "Interaction/Item.h"

// Sets default values
AItem::AItem()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;
	
}

// Called when the game starts or when spawned
void AItem::BeginPlay()
{
	Super::BeginPlay();
}

void AItem::Use_Implementation(AActor* Interactor)
{}

// Called every frame
void AItem::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void AItem::PickupItem_Implementation()
{}

void AItem::ReleaseItem_Implementation()
{
	
}

bool AItem::CanInteract_Implementation(AActor* Interactor, UPrimitiveComponent* Component) const
{
	return true;
}

void AItem::Interact_Implementation(AActor* Interactor, UPrimitiveComponent* Component)
{
	Use(Interactor);
}