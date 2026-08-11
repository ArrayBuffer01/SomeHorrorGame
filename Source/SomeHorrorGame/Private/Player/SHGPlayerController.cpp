// Fill out your copyright notice in the Description page of Project Settings.


#include "Player/SHGPlayerController.h"
#include "Game/SHGGameInstance.h"

void ASHGPlayerController::BeginPlay()
{
	GameInstance = GetGameInstance<USHGGameInstance>();

	GameInstance->RestoreInputSettings();
}
