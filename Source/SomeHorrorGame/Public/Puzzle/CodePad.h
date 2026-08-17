// SomeHorrorGame TM

#pragma once

#include "CoreMinimal.h"
#include "Puzzle/PuzzleActorBase.h"
#include "Interaction/Interactable.h"
#include "CodePad.generated.h"

/**
 * 
 */
UCLASS()
class SOMEHORRORGAME_API ACodePad : public APuzzleActorBase, public IInteractable
{
	GENERATED_BODY()
public:
	ACodePad();
	
	UFUNCTION(BlueprintCallable)
	void ResetInput();

	UFUNCTION(BlueprintCallable)
	void Input(FString Character);

	virtual void Interact_Implementation(AActor* Interactor, UPrimitiveComponent* Component) override;

	void CheckInput();
public:
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	TObjectPtr<UStaticMeshComponent> StaticMesh;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	FString CorrectCode;
	
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	FString CurrentInput;
};
