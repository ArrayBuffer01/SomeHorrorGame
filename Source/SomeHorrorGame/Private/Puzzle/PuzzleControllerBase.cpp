// SomeHorrorGame TM


#include "Puzzle/PuzzleControllerBase.h"
#include "Puzzle/PuzzleActorBase.h"

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
	Initialize();
}


void APuzzleControllerBase::Initialize()
{
	for (APuzzleActorBase* PuzzleActor : PuzzleActors)
	{
		PuzzleActor->StateChanged.AddUniqueDynamic(this, &APuzzleControllerBase::OnPuzzleActorStateChanged);
	}
}

void APuzzleControllerBase::OnPuzzleActorStateChanged(bool bIsSolved)
{
	// Optimization TM
	if (bSolved && !bIsSolved && bCanUnsolve)
	{
		UnSolve();
		return;
	}


	const bool bAllSolved = AreAllActorsSolved();

	if (!bSolved && bAllSolved)
		Solve();
	else if (bSolved && !bAllSolved && bCanUnsolve)
		UnSolve();

}

bool APuzzleControllerBase::AreAllActorsSolved() const
{
	for (APuzzleActorBase* PuzzleActor : PuzzleActors)
	{
		if (!PuzzleActor->IsSolved())
			return false;
	}

	return true;
}

// Called every frame
void APuzzleControllerBase::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void APuzzleControllerBase::Solve_Implementation()
{
	bSolved = true;
	PuzzleStateChanged.Broadcast(bSolved);
}

void APuzzleControllerBase::UnSolve_Implementation()
{
	bSolved = false;
	PuzzleStateChanged.Broadcast(bSolved);
}

