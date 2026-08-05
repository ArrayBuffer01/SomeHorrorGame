// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "SHGPlayer.generated.h"

// Forward declarations
class UInputMappingContext;
class UInputAction;
class UCameraComponent;

UCLASS()
class SOMEHORRORGAME_API ASHGPlayer : public ACharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	ASHGPlayer();
public:
	// Components
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Camera")
	TObjectPtr<UCameraComponent> Camera;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Item")
	USceneComponent* ItemHolderComponent;
protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;
public:
	// Input functions
	UFUNCTION()
	void Move(const FInputActionValue& Value);

	UFUNCTION()
	void Look(const FInputActionValue& Value);

	// Crouching functions
	UFUNCTION()
	void StartCrouch(const FInputActionValue& Value);

	UFUNCTION()
	void EndCrouch(const FInputActionValue& Value);

	UFUNCTION()
	void StartSprint(const FInputActionValue& Value);

	UFUNCTION()
	void EndSprint(const FInputActionValue& Value);

	UFUNCTION()
	void Interact(const FInputActionValue& Value);

	UFUNCTION()
	void Pickup(const FInputActionValue& Value);

	UFUNCTION()
	void UseItem(const FInputActionValue& Value);

	void CheckInteractable();

	UFUNCTION()
	void SelectItem(AItem* Item);

	UFUNCTION()
	bool AddItem(AItem* Item);

	UFUNCTION(BlueprintImplementableEvent, Category = "Interaction")
	void OnInteractableFocusChanged(AActor* NewInteractable);
public:
	// Movement speed properties
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Speed")
	float WalkSpeed;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Speed")
	float RunSpeed;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Speed")
	float CrouchSpeed;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category="Movement")
	bool bIsSprinting;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Movement")
	bool bCanJump;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Movement")
	bool bCanSprint;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Movement")
	bool bCanMove;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Movement")
	bool bCanLook;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Movement")
	bool bCanCrouch;

	// Interaction properties
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Interaction")
	TObjectPtr<AActor> CurrentInteractable;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Interaction")
	TObjectPtr<UPrimitiveComponent> CurrentInteractableComponent;

	// Input related properties
	UPROPERTY(EditAnywhere, Category = "Input")
	TObjectPtr<UInputMappingContext> InputMapping;

	// Input actions
	UPROPERTY(EditAnywhere, Category = "Input")
	TObjectPtr<UInputAction> MoveAction;

	UPROPERTY(EditAnywhere, Category = "Input")
	TObjectPtr<UInputAction> LookAction;

	UPROPERTY(EditAnywhere, Category = "Input")
	TObjectPtr<UInputAction> JumpAction;

	UPROPERTY(EditAnywhere, Category = "Input")
	TObjectPtr<UInputAction> InteractAction;

	UPROPERTY(EditAnywhere, Category = "Input")
	TObjectPtr<UInputAction> CrouchAction;

	UPROPERTY(EditAnywhere, Category = "Input")
	TObjectPtr<UInputAction> SprintAction;

	UPROPERTY(EditAnywhere, Category = "Input")
	TObjectPtr<UInputAction> PickupAction;

	UPROPERTY(EditAnywhere, Category = "Input")
	TObjectPtr<UInputAction> UseItemAction;

	// Inventory state
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Inventory")
	TObjectPtr<class UInventoryComponent> InventoryComponent;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Inventory")
	TObjectPtr<AItem> StarterItem;
};
