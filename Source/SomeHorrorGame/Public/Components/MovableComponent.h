// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/StaticMeshComponent.h"
#include "MovableComponent.generated.h"

UENUM(BlueprintType)
enum class EMovableState : uint8
{
	Closed,
	Open,
	Opening,
	Closing
};

/**
 * 
 */
UCLASS(ClassGroup=(Custom), meta = (BlueprintSpawnableComponent))
class SOMEHORRORGAME_API UMovableComponent : public UStaticMeshComponent
{
	GENERATED_BODY()
	UMovableComponent();
protected:
	virtual void BeginPlay() override;
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;
public:
	UFUNCTION(BlueprintCallable)
	void Open();
	UFUNCTION(BlueprintCallable)
	void Close();
	UFUNCTION(BlueprintCallable)
	void Toggle();
public:

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Movement")
	FTransform ClosedTransform;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Movement")
	FTransform OpenTransform;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Movement")
	float MoveDuration;

	UPROPERTY(BlueprintReadOnly)
	EMovableState State;
private:
	float m_fAlpha = 0.f;
	float m_fTargetAlpha = 0.f;
};
