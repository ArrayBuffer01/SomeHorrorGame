// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Interaction/Item.h"
#include "Flashlight.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnStateChanged, bool, bIsOn);

/**
 * 
 */
UCLASS()
class SOMEHORRORGAME_API AFlashlight : public AItem
{
	GENERATED_BODY()
	AFlashlight();
public:
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Flashlight")
	UStaticMeshComponent* FlashlightMesh;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Flashlight")
	class USpotLightComponent* Spotlight;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Flashlight")
	bool bIsOn;

	UPROPERTY(BlueprintAssignable)
	FOnStateChanged StateChanged;
public:
	UFUNCTION(BlueprintCallable, Category = "Flashlight")
	void ToggleFlashlight();

	virtual void OnConstruction(const FTransform& Transform) override;

	UFUNCTION(BlueprintImplementableEvent)
	void OnStateChange(const bool bNewState);

	void PickupItem_Implementation() override;
	void ReleaseItem_Implementation() override;
	void Use_Implementation(AActor* User) override;
};
