// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/GameInstance.h"
#include "SettingsSave.h"
#include "SHGGameInstance.generated.h"

#define SETTINGS_SLOTNAME TEXT("SHG_SETTINGS")
#define SETTINGS_SLOTINDEX 0

DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnSettingsSaved);


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

	UFUNCTION(BlueprintCallable)
	bool CaptureInputSettings();

	UFUNCTION(BlueprintCallable)
	bool RestoreInputSettings();
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

	UPROPERTY(BlueprintAssignable)
	FOnSettingsSaved OnSettingsSaved;

	static constexpr int CurrentInputVersion = 1;
};
