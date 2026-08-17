// SomeHorrorGame TM


#include "Puzzle/CodePad.h"

ACodePad::ACodePad()
{
	StaticMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("StaticMeshComponent"));
	SetRootComponent(StaticMesh);
	
	bCanUnsolve = false;
	CurrentInput = "";
}

void ACodePad::ResetInput()
{
	CurrentInput.Empty();
}

void ACodePad::Input(FString Character)
{
	const int Index = CurrentInput.Len();
	
	if (!CorrectCode.IsValidIndex(Index))
	{
		CurrentInput.Empty();
		return;
	}

	if (Character.IsEmpty())
	{
		return;
	}

	if (Character[0] != CorrectCode[Index])
	{
		CurrentInput.Empty();
		return;
	}

	CurrentInput += Character;
	CheckInput();		
}

void ACodePad::CheckInput()
{
	if (CurrentInput == CorrectCode)
	{
		Solve();
	}
	else if (bSolved && bCanUnsolve)
	{
		UnSolve();
	}
}

void ACodePad::Interact_Implementation(AActor* Interactor, UPrimitiveComponent* Component)
{
	// TODO: check which component was interacted with and based on that add the char/number that corresponds to it
	
	Input("0"); // Done in BP now.
}
