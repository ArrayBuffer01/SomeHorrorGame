// SomeHorrorGame TM

#include "Puzzle/ColorSwitcher.h"
#include "Components/SpotLightComponent.h"


AColorSwitcher::AColorSwitcher()
{
	
	StaticMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("StaticMesh"));
	//SpotlightComponent = CreateDefaultSubobject<USpotLightComponent>(TEXT("SpotlightComponent"));

	SetRootComponent(StaticMesh);
	//SpotlightComponent->SetupAttachment(StaticMesh);

	StaticMesh->SetMaterial(0, Material);

	CurrentColorIndex = 0;

	bCanUnsolve = true;
}

void AColorSwitcher::Interact_Implementation(AActor* Interactor, UPrimitiveComponent* Component)
{
	CurrentColorIndex = (CurrentColorIndex + 1) % Colors.Num();

	UpdateLightState();

	if (CurrentColorIndex == CorrectColorIndex)
	{
		Solve();
	}
	else if (bSolved)
	{
		UnSolve();
	}
}

bool AColorSwitcher::CanInteract_Implementation(AActor* Interactor, UPrimitiveComponent* Component) const
{
	return true;
}

void AColorSwitcher::OnConstruction(const FTransform& Transform)
{
	StaticMesh->SetMaterial(0, Material);
	UpdateLightState();
}

void AColorSwitcher::UpdateLightState()
{
	if (CurrentColorIndex >= Colors.Num())
		return;

	// SpotlightComponent->SetLightColor(Colors[CurrentColorIndex]);

	StaticMesh->SetColorParameterValueOnMaterials(TEXT("Color"), Colors[CurrentColorIndex]);
}
