// SomeHorrorGame TM

#include "Puzzle/ColorSwitcher.h"
#include "Components/SpotLightComponent.h"


AColorSwitcher::AColorSwitcher()
{
	
	StaticMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("StaticMesh"));
	SpotlightComponent = CreateDefaultSubobject<USpotLightComponent>(TEXT("SpotlightComponent"));

	SetRootComponent(StaticMesh);
	SpotlightComponent->SetupAttachment(StaticMesh);

	CurrentColorIndex = 0;
}

void AColorSwitcher::Interact_Implementation(AActor* Interactor, UPrimitiveComponent* Component)
{
	CurrentColorIndex = (CurrentColorIndex + 1) % Colors.Num();

	// UpdateLightState();

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

void AColorSwitcher::UpdateLightState()
{
	SpotlightComponent->LightColor = Colors[CurrentColorIndex];
}
