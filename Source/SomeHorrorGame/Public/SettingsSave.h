// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/SaveGame.h"
#include "SettingsSave.generated.h"


USTRUCT(BlueprintType)
struct FControlsSettings
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Mouse")
	bool bInvertMouse = false;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Mouse")
	float MouseSensitivity = 1.0f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Crosshair")
	bool bShowCrosshair = true;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Crosshair")
	bool bIsCrosshairInteractive = true;
};

USTRUCT(BlueprintType)
struct FSHGAudioSettings
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Audio")
	float MasterVolume = 1.0f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Audio")
	float AmbienceVolume = 1.0f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Audio")
	float EffectsVolume = 1.0f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Audio")
	float MusicVolume = 1.0f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Audio")
	float VHSVolume = 1.0f;
};

USTRUCT(BlueprintType)
struct FSettingsData
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Mouse")
	FSHGAudioSettings AudioSettings;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Mouse")
	FControlsSettings ControlsSettings;

	UPROPERTY()
	int InputDataVersion = 1;

	UPROPERTY()
	TArray<uint8> InputData;
};

/**
 * 
 */
UCLASS()
class SOMEHORRORGAME_API USettingsSave : public USaveGame
{
	GENERATED_BODY()
public:
	USettingsSave();
public:
	UPROPERTY(BlueprintReadOnly)
	FSettingsData SettingsData;
};

/*
TODO: Maybe add setters in future, too lazy rn :Tm:
void USHGGameInstance::SetMouseSensitivity(const float NewSens)
{
	Settings.MouseSensitivity = NewSens;
}

void USHGGameInstance::SetInvertMouse(const bool bInvertMouse)
{
	Settings.bInvertMouse = bInvertMouse;
}

void USHGGameInstance::SetAmbienceVolume(const float NewVolume)
{
	Settings.AmbienceVolume = NewVolume;
}

void USHGGameInstance::SetEffectsVolume(const float NewVolume)
{
	Settings.EffectsVolume = NewVolume;
}

void USHGGameInstance::SetMusicVolume(const float NewVolume)
{
	Settings.MusicVolume = NewVolume;
}

void USHGGameInstance::SetVHSVolume(const float NewVolume)
{
	Settings.VHSVolume = NewVolume;
}

*/