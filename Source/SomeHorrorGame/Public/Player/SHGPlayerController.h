// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "SHGPlayerController.generated.h"

class USHGGameInstance;

/**
 * 
 */
UCLASS()
class SOMEHORRORGAME_API ASHGPlayerController : public APlayerController
{
	GENERATED_BODY()
public:
	UPROPERTY(BlueprintReadOnly)
	TObjectPtr<USHGGameInstance> GameInstance;
public:
	void BeginPlay() override;
};
