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

	virtual void OnConstruction(const FTransform& Transform) override;

	void UpdateLightState();
public:
	// Components
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	TObjectPtr<UStaticMeshComponent> StaticMesh;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	TObjectPtr<USpotLightComponent> SpotlightComponent;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	TObjectPtr<UMaterialInterface> Material;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TArray<FLinearColor> Colors;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int CurrentColorIndex;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int CorrectColorIndex;
};
