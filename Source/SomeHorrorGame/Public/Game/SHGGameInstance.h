// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/GameInstance.h"
#include "SHGGameInstance.generated.h"

/**
 * 
 */
UCLASS()
class SOMEHORRORGAME_API USHGGameInstance : public UGameInstance
{
	GENERATED_BODY()
public:
	// Methods
	UFUNCTION(BlueprintCallable)
	void SetPlayerName(const FString& NewPlayerName);
public:
	UPROPERTY(BlueprintReadWrite)
	FString PlayerName;

	UPROPERTY(BlueprintReadWrite)
	int DeathCount;

	UPROPERTY(BlueprintReadWrite)
	bool bIsFirstTimePlaying;
};
