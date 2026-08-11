// Fill out your copyright notice in the Description page of Project Settings.

#include "Objects/Door.h"
#include "Components/MovableComponent.h"

// Sets default values
ADoor::ADoor()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	SceneComp = CreateDefaultSubobject<USceneComponent>(TEXT("SceneComp"));
	DoorMesh = CreateDefaultSubobject<UMovableComponent>(TEXT("DoorMesh"));

	SetRootComponent(SceneComp);

	DoorMesh->SetupAttachment(RootComponent);
}

// Called when the game starts or when spawned
void ADoor::BeginPlay()
{
	Super::BeginPlay();
}

// Called every frame
void ADoor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

bool ADoor::CanInteract_Implementation(AActor* Interactor, UPrimitiveComponent* Component) const
{
	return Component == DoorMesh;
}

void ADoor::Interact_Implementation(AActor* Interactor, UPrimitiveComponent* Component)
{
	if (Component == DoorMesh)
	{
		DoorMesh->Toggle();
	}
}
