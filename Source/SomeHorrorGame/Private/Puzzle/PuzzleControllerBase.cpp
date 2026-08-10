// SomeHorrorGame TM


#include "Puzzle/PuzzleControllerBase.h"

// Sets default values
APuzzleControllerBase::APuzzleControllerBase()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void APuzzleControllerBase::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void APuzzleControllerBase::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

