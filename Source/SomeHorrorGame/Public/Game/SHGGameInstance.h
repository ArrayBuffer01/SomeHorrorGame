// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/GameInstance.h"
#include "SettingsSave.h"
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

	virtual void Init() override;

	UFUNCTION(BlueprintCallable)
	void SaveSettings();

	UFUNCTION(BlueprintImplementableEvent)
	void OnLoad();
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
	TObjectPtr<USettingsSave> Settings;
};
