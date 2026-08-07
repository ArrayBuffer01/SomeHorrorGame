// Fill out your copyright notice in the Description page of Project Settings.

#include "Game/SHGGameInstance.h"
#include "SettingsSave.h"
#include "Kismet/GameplayStatics.h"

#define SETTINGS_SLOTNAME TEXT("SHG_SETTINGS")
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

	if (UGameplayStatics::DoesSaveGameExist(SETTINGS_SLOTNAME, 0))
	{
		Settings = Cast<USettingsSave>(UGameplayStatics::LoadGameFromSlot(SETTINGS_SLOTNAME, 0));
	}
	else
	{
		Settings = Cast<USettingsSave>(UGameplayStatics::CreateSaveGameObject(USettingsSave::StaticClass()));
		SaveSettings();
	}

	OnLoad();
}

void USHGGameInstance::SaveSettings()
{
	UGameplayStatics::SaveGameToSlot(Settings, SETTINGS_SLOTNAME, 0);
}

void USHGGameInstance::SetPlayerName(const FString& NewPlayerName)
{
	PlayerName = NewPlayerName;
}
