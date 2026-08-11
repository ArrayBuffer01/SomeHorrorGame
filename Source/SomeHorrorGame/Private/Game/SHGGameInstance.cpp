// Fill out your copyright notice in the Description page of Project Settings.

#include "Game/SHGGameInstance.h"
#include "SettingsSave.h"
#include "EnhancedInputSubsystems.h"
#include "UserSettings/EnhancedInputUserSettings.h"
#include "Serialization/MemoryWriter.h"
#include "Serialization/MemoryReader.h"
#include "Kismet/GameplayStatics.h"

void USHGGameInstance::Init()
{
	Super::Init();

	// Init default values

	DeathCount = 0;

	const bool bSaveExists = UGameplayStatics::DoesSaveGameExist(TEXT("SHG_SAV_001"), 0);

	if (bSaveExists)
	{
		bIsFirstTimePlaying = false;
		// TODO: Load player name and death count from the save game object
	}
	else
	{
		bIsFirstTimePlaying = true;
	}

	if (UGameplayStatics::DoesSaveGameExist(SETTINGS_SLOTNAME, SETTINGS_SLOTINDEX))
	{
		Settings = Cast<USettingsSave>(UGameplayStatics::LoadGameFromSlot(SETTINGS_SLOTNAME, SETTINGS_SLOTINDEX));
	}
	else
	{
		Settings = Cast<USettingsSave>(UGameplayStatics::CreateSaveGameObject(USettingsSave::StaticClass()));
	}

	OnLoad();
}

void USHGGameInstance::SaveSettings()
{
	CaptureInputSettings();

	OnSettingsSaved.Broadcast();
	
	UGameplayStatics::SaveGameToSlot(Settings, SETTINGS_SLOTNAME, SETTINGS_SLOTINDEX);
}

bool USHGGameInstance::CaptureInputSettings()
{
	ULocalPlayer* LocalPlayer = GetLocalPlayerByIndex(0);

	if (!LocalPlayer)
		return false;

	UEnhancedInputLocalPlayerSubsystem* InputSubsystem = LocalPlayer->GetSubsystem<UEnhancedInputLocalPlayerSubsystem>();

	if (!InputSubsystem)
	{
		return false;
	}

	UEnhancedInputUserSettings* UserSettings = InputSubsystem->GetUserSettings();

	if (!UserSettings)
	{
		return false;
	}

	TArray<uint8>& SerializedData = Settings->SettingsData.InputData;

	SerializedData.Reset();

	FMemoryWriter Writer(SerializedData, true);

	UserSettings->Serialize(Writer);

	if (Writer.IsError())
	{
		SerializedData.Reset();
		return false;
	}

	Settings->SettingsData.InputDataVersion = CurrentInputVersion;

	return true;
}

bool USHGGameInstance::RestoreInputSettings()
{
	ULocalPlayer* LocalPlayer = GetLocalPlayerByIndex(0);

	if (!LocalPlayer)
		return false;

	UEnhancedInputLocalPlayerSubsystem* InputSubsystem = LocalPlayer->GetSubsystem<UEnhancedInputLocalPlayerSubsystem>();

	if (!InputSubsystem)
	{
		return false;
	}

	UEnhancedInputUserSettings* UserSettings = InputSubsystem->GetUserSettings();

	if (!UserSettings)
	{
		return false;
	}

	if (Settings->SettingsData.InputData.IsEmpty())
	{
		return true;
	}

	FMemoryReader Reader(Settings->SettingsData.InputData, true);

	UserSettings->Serialize(Reader);

	UserSettings->ApplySettings();

	return true;
}

void USHGGameInstance::SetPlayerName(const FString& NewPlayerName)
{
	PlayerName = NewPlayerName;
}
