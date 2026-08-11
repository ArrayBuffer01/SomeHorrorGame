// SomeHorrorGame TM

#pragma once

#include "CoreMinimal.h"
#include "Puzzle/PuzzleActorBase.h"
#include "Interaction/Interactable.h"
#include "ColorSwitcher.generated.h"

class USpotLightComponent;

/**
 * 
 */
UCLASS()
class SOMEHORRORGAME_API AColorSwitcher : public APuzzleActorBase, public IInteractable
{
	GENERATED_BODY()
public:
	AColorSwitcher();

	void Interact_Implementation(AActor* Interactor, UPrimitiveComponent* Component) override;
	bool CanInteract_Implementation(AActor* Interactor, UPrimitiveComponent* Component) const override;

	void UpdateLightState();
public:
	// Components
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	TObjectPtr<UStaticMeshComponent> StaticMesh;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	TObjectPtr<USpotLightComponent> SpotlightComponent;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TArray<FColor> Colors;

	UPROPERTY()
	int CurrentColorIndex;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int CorrectColorIndex;
};
