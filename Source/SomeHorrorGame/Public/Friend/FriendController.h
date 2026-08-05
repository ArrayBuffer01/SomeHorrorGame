// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AIController.h"
#include "FriendController.generated.h"

class UBehaviorTreeComponent;
class UBlackboardComponent;
class UBehaviorTree;
class UAIPerceptionComponent;
class UAISenseConfig_Sight;
class UAISenseConfig_Hearing;

UENUM(BlueprintType)
enum class EFriendState : uint8
{
	None,
	Patrolling,
	Investigating,
	Chasing
};

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnStateChange, EFriendState, NewState);

/**
 * 
 */
UCLASS()
class SOMEHORRORGAME_API AFriendController : public AAIController
{
	GENERATED_BODY()
public:
	AFriendController();
	virtual void BeginPlay() override;
	UFUNCTION(BlueprintPure)
	EFriendState GetState() const { return CurrentState; }
	UFUNCTION(BlueprintCallable)
	void SetState(EFriendState State);

	UFUNCTION(BlueprintCallable)
	void SetLastPlayerLocation(FVector Location);

	virtual void OnPossess(APawn* InPawn) override;
public:
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	EFriendState CurrentState;

	UPROPERTY(BlueprintAssignable)
	FOnStateChange OnStateChange;

	UPROPERTY(BlueprintReadOnly)
	FVector LastPlayerLocation;

	UPROPERTY(BlueprintReadOnly)
	TArray<FVector> RecentTrapLocations;
public:
	UPROPERTY(EditAnywhere, Category="AI")
	TObjectPtr<UBehaviorTree> BehaviorTree;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category="AI")
	TObjectPtr<UAIPerceptionComponent> PerceptionComp;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "AI")
	TObjectPtr<UAISenseConfig_Sight> SightConfig;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "AI")
	TObjectPtr<UAISenseConfig_Hearing> HearingConfig;

	UFUNCTION()
	void OnTargetPerceptionUpdated(AActor* Actor, FAIStimulus Stimulus);
};
