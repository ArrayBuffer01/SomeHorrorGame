// Fill out your copyright notice in the Description page of Project Settings.

#include "Game/SHGGameInstance.h"
#include "Kismet/GameplayStatics.h"


void USHGGameInstance::Init()
{
	Super::Init();

	// Init default values

	DeathCount = 0;

	const bool bSaveExists = UGameplayStatics::DoesSaveGameExist(TEXT("SOMEHORRORGAME_SAV_001"), 0);

	if (bSaveExists)
	{
		bIsFirstTimePlaying = false;
		// TODO: Load player name and death count from the save game object
	}
	else
	{
		bIsFirstTimePlaying = true;
	}
}

void USHGGameInstance::SetPlayerName(const FString& NewPlayerName)
{
	PlayerName = NewPlayerName;
}

void USHGGameInstance::SetMouseSensitivity(const float NewSens)
{
	Settings.MouseSensitivity = NewSens;
}

void USHGGameInstance::SetInvertMouse(const bool bInvertMouse)
{
	Settings.bInvertMouse = bInvertMouse;
}
