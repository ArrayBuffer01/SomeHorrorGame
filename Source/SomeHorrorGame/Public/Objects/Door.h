// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Interaction/Interactable.h"
#include "GameFramework/Actor.h"
#include "Door.generated.h"

class UMovableComponent;

UCLASS()
class SOMEHORRORGAME_API ADoor : public AActor, public IInteractable
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ADoor();

public:
	// Components
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	TObjectPtr<USceneComponent> SceneComp;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	TObjectPtr<UMovableComponent> DoorMesh;

	UPROPERTY(BlueprintReadOnly)
	bool bIsOpen;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	bool bIsLocked;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FName DoorNameForSave;
public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;
	
	virtual bool CanInteract_Implementation(AActor* Interactor, UPrimitiveComponent* Component) const override;
	virtual void Interact_Implementation(AActor* Interactor, UPrimitiveComponent* Component) override;
};
