// Fill out your copyright notice in the Description page of Project Settings.


#include "Components/MovableComponent.h"

UMovableComponent::UMovableComponent()
{
	PrimaryComponentTick.bCanEverTick = true;
	PrimaryComponentTick.bStartWithTickEnabled = false;

	State = EMovableState::Closed;
}

void UMovableComponent::BeginPlay()
{
	Super::BeginPlay();
}

void UMovableComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);
	const float InterpSpeed = 1.0f / FMath::Max(MoveDuration, KINDA_SMALL_NUMBER);
	// Update the alpha value towards the target alpha
	m_fAlpha = FMath::FInterpConstantTo(m_fAlpha, m_fTargetAlpha, DeltaTime, InterpSpeed);

	const bool bFinished = FMath::IsNearlyEqual(m_fAlpha, m_fTargetAlpha, KINDA_SMALL_NUMBER);

	if (bFinished)
	{
		m_fAlpha = m_fTargetAlpha;
		State = (m_fTargetAlpha > 0.5f) ? EMovableState::Open : EMovableState::Closed;
	}

	// Interpolate between the closed and open transforms based on the alpha value
	FTransform NewTransform;
	NewTransform.Blend(ClosedTransform, OpenTransform, m_fAlpha);
	// Apply the new transform to the component
	SetRelativeTransform(NewTransform);

	if (bFinished)
	{
		SetComponentTickEnabled(false);
	}
}

void UMovableComponent::Open()
{
	if (State == EMovableState::Open || State == EMovableState::Opening)
	{
		return;
	}

	State = EMovableState::Opening;
	m_fTargetAlpha = 1.0f;
	SetComponentTickEnabled(true);
}

void UMovableComponent::Close()
{
	if (State == EMovableState::Closed || State == EMovableState::Closing)
	{
		return;
	}

	State = EMovableState::Closing;
	m_fTargetAlpha = 0.0f;
	SetComponentTickEnabled(true);
}

void UMovableComponent::Toggle()
{
	switch (State)
	{
	case EMovableState::Closed:
	case EMovableState::Closing:
		Open();
		break;
	case EMovableState::Open:
	case EMovableState::Opening:
		Close();
		break;
	}
}