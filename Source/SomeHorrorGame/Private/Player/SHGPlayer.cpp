	// Fill out your copyright notice in the Description page of Project Settings.

#include "Player/SHGPlayer.h"
#include "EnhancedInputSubsystems.h"
#include "EnhancedInputComponent.h"
#include "Camera/CameraComponent.h"
#include "Components/InventoryComponent.h"
#include "Interaction/Item.h"
#include "Interaction/Interactable.h"
#include "GameFramework/CharacterMovementComponent.h"

// Sets default values
ASHGPlayer::ASHGPlayer()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	// Create camera component and attach it to the root component and position it at the player's head
	Camera = CreateDefaultSubobject<UCameraComponent>(TEXT("Camera"));
	Camera->SetupAttachment(RootComponent);
	Camera->SetRelativeLocation(FVector(20.f, 0.f, 70.f));

	// Setup inventory
	InventoryComponent = CreateDefaultSubobject<UInventoryComponent>(TEXT("InventoryComponent"));
	ItemHolderComponent = CreateDefaultSubobject<USceneComponent>(TEXT("ItemHolderComponent"));

	ItemHolderComponent->SetupAttachment(Camera);

	// Set camera properties
	Camera->bUsePawnControlRotation = true;

	// Set default speed values
	WalkSpeed = 350.f;
	RunSpeed = 700.f;
	CrouchSpeed = 175.f;

	// Movement flags
	bCanJump = true;
	bCanSprint = true;
	bCanLook = true;
	bCanMove = true;
	bCanCrouch = true;

	// Set default movement properties
	GetCharacterMovement()->MaxWalkSpeed = WalkSpeed;
	GetCharacterMovement()->MaxWalkSpeedCrouched = CrouchSpeed;
	GetCharacterMovement()->NavAgentProps.bCanCrouch = true;
}

// Called when the game starts or when spawned
void ASHGPlayer::BeginPlay()
{
	Super::BeginPlay();

	if (StarterItem)
	{
		const bool bSuccess = AddItem(StarterItem);
		if (bSuccess)
		{
			SelectItem(StarterItem);
		}
	}
}

bool ASHGPlayer::AddItem(AItem* Item)
{
	if (!Item) return false;

	int Index = InventoryComponent->AddItem(Item);

	if (Index != INDEX_NONE)
	{
		Item->SetActorEnableCollision(false);
		Item->SetActorHiddenInGame(true);

		Item->AttachToComponent(ItemHolderComponent, FAttachmentTransformRules::SnapToTargetNotIncludingScale);

		Item->SetActorRelativeTransform(Item->ItemData.HandOffset);
	}

	return Index != INDEX_NONE;
}


void ASHGPlayer::SelectItem(AItem* Item)
{
	if (!Item) return;

	if (InventoryComponent->CurrentItem && InventoryComponent->CurrentItem != Item)
	{
		InventoryComponent->CurrentItem->SetActorHiddenInGame(true);
	}
	
	const bool bSuccess = InventoryComponent->SelectItem(Item);

	if (bSuccess)
	{
		Item->SetActorHiddenInGame(false);
	}
}

// Called every frame
void ASHGPlayer::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	CheckInteractable();
}

// Called to bind functionality to input
void ASHGPlayer::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);
	if (APlayerController* playerController = Cast<APlayerController>(GetController()))
	{
		if (UEnhancedInputLocalPlayerSubsystem* subsystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(playerController->GetLocalPlayer()))
		{
			// Clear mappings
			subsystem->ClearAllMappings();
			// Add mapping context
			subsystem->AddMappingContext(InputMapping, 0);

			if (UEnhancedInputComponent* enhancedInputComponent = Cast<UEnhancedInputComponent>(PlayerInputComponent))
			{
				if (MoveAction)
				{
					enhancedInputComponent->BindAction(MoveAction, ETriggerEvent::Triggered, this, &ASHGPlayer::Move);
				}

				if (JumpAction)
				{
					enhancedInputComponent->BindAction(JumpAction, ETriggerEvent::Started, this, &ASHGPlayer::Jump);
					enhancedInputComponent->BindAction(JumpAction, ETriggerEvent::Completed, this, &ASHGPlayer::StopJumping);
				}

				if (SprintAction)
				{
					enhancedInputComponent->BindAction(SprintAction, ETriggerEvent::Started, this, &ASHGPlayer::StartSprint);
					enhancedInputComponent->BindAction(SprintAction, ETriggerEvent::Completed, this, &ASHGPlayer::EndSprint);
				}

				if (LookAction)
				{
					enhancedInputComponent->BindAction(LookAction, ETriggerEvent::Triggered, this, &ASHGPlayer::Look);
				}

				if (CrouchAction)
				{
					enhancedInputComponent->BindAction(CrouchAction, ETriggerEvent::Started, this, &ASHGPlayer::StartCrouch);
					//enhancedInputComponent->BindAction(CrouchAction, ETriggerEvent::Completed, this, &ASHGPlayer::EndCrouch);
				}

				if (InteractAction)
				{
					enhancedInputComponent->BindAction(InteractAction, ETriggerEvent::Started, this, &ASHGPlayer::Interact);
					//enhancedInputComponent->BindAction(CrouchAction, ETriggerEvent::Completed, this, &ASHGPlayer::EndCrouch);
				}

				if (PickupAction)
				{
					enhancedInputComponent->BindAction(PickupAction, ETriggerEvent::Started, this, &ASHGPlayer::Pickup);
				}

				if (UseItemAction)
				{
					enhancedInputComponent->BindAction(UseItemAction, ETriggerEvent::Started, this, &ASHGPlayer::UseItem);
				}
			}
		}
	}
}

// Input handling actions
void ASHGPlayer::Move(const FInputActionValue& Value)
{
	if (!bCanMove) return;

	FVector2D inputVector = Value.Get<FVector2D>();

	AddMovementInput(GetActorForwardVector(), inputVector.Y);
	AddMovementInput(GetActorRightVector(), inputVector.X);
}

void ASHGPlayer::Look(const FInputActionValue& Value)
{
	if (!bCanLook) return;

	FVector2D inputVector = Value.Get<FVector2D>();

	AddControllerYawInput(inputVector.X);
	AddControllerPitchInput(inputVector.Y);
}

void ASHGPlayer::StartCrouch(const FInputActionValue& Value)
{
	if (!bCanCrouch) return;
	IsCrouched() ? UnCrouch() : Crouch();
}

void ASHGPlayer::EndCrouch(const FInputActionValue& Value)
{
	UnCrouch();
}

void ASHGPlayer::Pickup(const FInputActionValue& Value)
{
	if (IsValid(CurrentInteractable))
	{
		if (AItem* Item = Cast<AItem>(CurrentInteractable))
		{
			bool bSuccess = AddItem(Item);

			if (bSuccess)
			{
				CurrentInteractable = nullptr;
				CurrentInteractableComponent = nullptr;

				SelectItem(Item);
			}
		}
	}
}

void ASHGPlayer::UseItem(const FInputActionValue& Value)
{
	if (InventoryComponent->CurrentItem)
	{
		InventoryComponent->CurrentItem->Use(this);
	}
}

void ASHGPlayer::StartSprint(const FInputActionValue& Value)
{
	if (!bCanSprint) return;

	bIsSprinting = true;
	GetCharacterMovement()->MaxWalkSpeed = RunSpeed;
}

void ASHGPlayer::EndSprint(const FInputActionValue & Value)
{
	bIsSprinting = false;
	GetCharacterMovement()->MaxWalkSpeed = WalkSpeed;
}

void ASHGPlayer::Interact(const FInputActionValue& Value)
{
	if (IsValid(CurrentInteractable))
	{
		IInteractable::Execute_Interact(CurrentInteractable, this, CurrentInteractableComponent);
	}
}

void ASHGPlayer::CheckInteractable()
{
	FVector Start = Camera->GetComponentLocation();
	FVector End = Start + Camera->GetForwardVector() * 300;

	FHitResult Hit;

	FCollisionQueryParams Params;
	Params.AddIgnoredActor(this);

	bool bHit = GetWorld()->LineTraceSingleByChannel(
		Hit,
		Start,
		End,
		ECC_Visibility,
		Params
	);
	
	AActor* newInteractable = nullptr;
	CurrentInteractableComponent = Hit.GetComponent();

	if (bHit)
	{
		if (AActor* HitActor = Hit.GetActor())
		{
			if (HitActor->GetClass()->ImplementsInterface(UInteractable::StaticClass()) && IInteractable::Execute_CanInteract(HitActor, this, CurrentInteractableComponent))
			{
				newInteractable = HitActor;
			}
		}
	}

	if (CurrentInteractable != newInteractable)
	{
		if (IsValid(CurrentInteractable))
		{
			IInteractable::Execute_OnFocusEnd(CurrentInteractable, this, CurrentInteractableComponent);
		}

		CurrentInteractable = newInteractable;

		if (IsValid(CurrentInteractable))
		{
			IInteractable::Execute_OnFocusStart(CurrentInteractable, this, CurrentInteractableComponent);
		}

		OnInteractableFocusChanged(CurrentInteractable);
	}
}
