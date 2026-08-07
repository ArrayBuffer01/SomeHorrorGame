// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/GameInstance.h"
#include "SHGGameInstance.generated.h"

USTRUCT(BlueprintType)
struct FSettingsData
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Mouse")
	bool bInvertMouse = false;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Mouse")
	float MouseSensitivity = 1.0f;
};

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

	UFUNCTION(BlueprintCallable)
	void SetMouseSensitivity(const float NewSens);

	UFUNCTION(BlueprintCallable)
	void SetInvertMouse(const bool bInvertMouse);


	virtual void Init() override;
public:
	UPROPERTY(BlueprintReadWrite)
	FString PlayerName;

	UPROPERTY(BlueprintReadWrite)
	int DeathCount;

	UPROPERTY(BlueprintReadWrite)
	bool bIsFirstTimePlaying;

	UPROPERTY(BlueprintReadWrite)
	bool bIsNewGame;

	UPROPERTY(BlueprintReadOnly)
	FSettingsData Settings;
};
