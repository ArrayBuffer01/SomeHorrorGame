// Fill out your copyright notice in the Description page of Project Settings.


#include "Interaction/Interactable.h"

// Add default functionality here for any IInteractable functions that are not pure virtual.

void IInteractable::Interact_Implementation(AActor* Interactor, UPrimitiveComponent* Component)
{}

bool IInteractable::CanInteract_Implementation(AActor * Interactor, UPrimitiveComponent * Component) const
{
	return false;
}

void IInteractable::OnFocusStart_Implementation(AActor* Interactor, UPrimitiveComponent* Component)
{}

void IInteractable::OnFocusEnd_Implementation(AActor * Interactor, UPrimitiveComponent * Component)
{}
