// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "Interactable.generated.h"

// This class does not need to be modified.
UINTERFACE(MinimalAPI)
class UInteractable : public UInterface
{
	GENERATED_BODY()
};

/**
 * 
 */
class SOMEHORRORGAME_API IInteractable
{
	GENERATED_BODY()

public:
	UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category="Interaction")
	void Interact(AActor* Interactor, UPrimitiveComponent* Component);
	virtual void Interact_Implementation(AActor* Interactor, UPrimitiveComponent* Component);

	UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category="Interaction")
	bool CanInteract(AActor* Interactor, UPrimitiveComponent* Component) const;
	virtual bool CanInteract_Implementation(AActor* Interactor, UPrimitiveComponent* Component) const;

	UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category = "Interaction")
	void OnFocusStart(AActor* Interactor, UPrimitiveComponent* Component);
	virtual void OnFocusStart_Implementation(AActor* Interactor, UPrimitiveComponent* Component);

	UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category = "Interaction")
	void OnFocusEnd(AActor* Interactor, UPrimitiveComponent* Component);
	virtual void OnFocusEnd_Implementation(AActor* Interactor, UPrimitiveComponent* Component);
};
