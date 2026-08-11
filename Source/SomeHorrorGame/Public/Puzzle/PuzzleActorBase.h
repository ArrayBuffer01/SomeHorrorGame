// SomeHorrorGame TM

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "PuzzleActorBase.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnPuzzleActorStateChanged, bool, bIsSolved);


UCLASS()
class SOMEHORRORGAME_API APuzzleActorBase : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	APuzzleActorBase();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	UFUNCTION(BlueprintCallable, BlueprintNativeEvent)
	void Solve();
	void Solve_Implementation();

	UFUNCTION(BlueprintCallable, BlueprintNativeEvent)
	void UnSolve();
	void UnSolve_Implementation();

	UFUNCTION(BlueprintPure)
	bool IsSolved() const;
public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	bool bCanUnsolve;

	UPROPERTY(BlueprintReadOnly)
	bool bSolved;

	UPROPERTY(BlueprintAssignable)
	FOnPuzzleActorStateChanged StateChanged;
};
