	// Fill out your copyright notice in the Description page of Project Settings.

#include "Player/SHGPlayer.h"
#include "EnhancedInputSubsystems.h"
#include "EnhancedInputComponent.h"
#include "Camera/CameraComponent.h"
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


	// Set camera properties
	Camera->bUsePawnControlRotation = true;

	// Set default speed values
	m_fWalkSpeed = 350.f;
	m_fRunSpeed = 700.f;
	m_fCrouchSpeed = 175.f;

	// Movement flags
	bCanJump = true;
	bCanSprint = true;
	bCanLook = true;
	bCanMove = true;
	bCanCrouch = true;

	// Set default movement properties
	GetCharacterMovement()->MaxWalkSpeed = m_fWalkSpeed;
	GetCharacterMovement()->MaxWalkSpeedCrouched = m_fCrouchSpeed;
	GetCharacterMovement()->NavAgentProps.bCanCrouch = true;
}

// Called when the game starts or when spawned
void ASHGPlayer::BeginPlay()
{
	Super::BeginPlay();
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
			subsystem->AddMappingContext(m_pInputMapping, 0);

			if (UEnhancedInputComponent* enhancedInputComponent = Cast<UEnhancedInputComponent>(PlayerInputComponent))
			{
				if (m_pMoveAction)
				{
					enhancedInputComponent->BindAction(m_pMoveAction, ETriggerEvent::Triggered, this, &ASHGPlayer::Move);
				}

				if (m_pJumpAction)
				{
					enhancedInputComponent->BindAction(m_pJumpAction, ETriggerEvent::Started, this, &ASHGPlayer::Jump);
					enhancedInputComponent->BindAction(m_pJumpAction, ETriggerEvent::Completed, this, &ASHGPlayer::StopJumping);
				}

				if (m_pSprintAction)
				{
					enhancedInputComponent->BindAction(m_pSprintAction, ETriggerEvent::Started, this, &ASHGPlayer::StartSprint);
					enhancedInputComponent->BindAction(m_pSprintAction, ETriggerEvent::Completed, this, &ASHGPlayer::EndSprint);
				}

				if (m_pLookAction)
				{
					enhancedInputComponent->BindAction(m_pLookAction, ETriggerEvent::Triggered, this, &ASHGPlayer::Look);
				}

				if (m_pCrouchAction)
				{
					enhancedInputComponent->BindAction(m_pCrouchAction, ETriggerEvent::Started, this, &ASHGPlayer::StartCrouch);
					//enhancedInputComponent->BindAction(m_pCrouchAction, ETriggerEvent::Completed, this, &ASHGPlayer::EndCrouch);
				}

				if (m_pInteractAction)
				{
					enhancedInputComponent->BindAction(m_pInteractAction, ETriggerEvent::Started, this, &ASHGPlayer::Interact);
					//enhancedInputComponent->BindAction(m_pCrouchAction, ETriggerEvent::Completed, this, &ASHGPlayer::EndCrouch);
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

void ASHGPlayer::StartSprint(const FInputActionValue& Value)
{
	if (!bCanSprint) return;

	bIsSprinting = true;
	GetCharacterMovement()->MaxWalkSpeed = m_fRunSpeed;
}

void ASHGPlayer::EndSprint(const FInputActionValue & Value)
{
	bIsSprinting = false;
	GetCharacterMovement()->MaxWalkSpeed = m_fWalkSpeed;
}

void ASHGPlayer::Interact(const FInputActionValue& Value)
{
	if (IsValid(m_pCurrentInteractable))
	{
		IInteractable::Execute_Interact(m_pCurrentInteractable, this, m_pCurrentInteractableComponent);
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
	m_pCurrentInteractableComponent = Hit.GetComponent();

	if (bHit)
	{
		if (AActor* HitActor = Hit.GetActor())
		{
			if (HitActor->GetClass()->ImplementsInterface(UInteractable::StaticClass()) && IInteractable::Execute_CanInteract(HitActor, this, m_pCurrentInteractableComponent))
			{
				newInteractable = HitActor;
			}
		}
	}

	if (m_pCurrentInteractable != newInteractable)
	{
		if (IsValid(m_pCurrentInteractable))
		{
			IInteractable::Execute_OnFocusEnd(m_pCurrentInteractable, this, m_pCurrentInteractableComponent);
		}

		m_pCurrentInteractable = newInteractable;

		if (IsValid(m_pCurrentInteractable))
		{
			IInteractable::Execute_OnFocusStart(m_pCurrentInteractable, this, m_pCurrentInteractableComponent);
		}

		OnInteractableFocusChanged(m_pCurrentInteractable);
	}
}
