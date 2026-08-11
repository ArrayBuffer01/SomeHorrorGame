// SomeHorrorGame TM

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "PuzzleControllerBase.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnPuzzleStateChanged, bool, bIsSolved);

class APuzzleActorBase;

UCLASS()
class SOMEHORRORGAME_API APuzzleControllerBase : public AActor
{
	GENERATED_BODY()

public:	
	// Sets default values for this actor's properties
	APuzzleControllerBase();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	void Initialize();

public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	bool bCanUnsolve;

	UPROPERTY(BlueprintReadOnly)
	bool bSolved;

	UPROPERTY(EditAnywhere)
	TArray<TObjectPtr<APuzzleActorBase>> PuzzleActors;

	UPROPERTY(BlueprintAssignable)
	FOnPuzzleStateChanged PuzzleStateChanged;


public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;
	bool AreAllActorsSolved() const;

	UFUNCTION()
	void OnPuzzleActorStateChanged(bool bIsSolved);

	UFUNCTION(BlueprintCallable, BlueprintNativeEvent)
	void Solve();
	void Solve_Implementation();

	UFUNCTION(BlueprintCallable, BlueprintNativeEvent)
	void UnSolve();
	void UnSolve_Implementation();
};
