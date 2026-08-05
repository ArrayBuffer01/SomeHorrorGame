// Fill out your copyright notice in the Description page of Project Settings.


#include "Game/SHGGameMode.h"
#include "Player/SHGPlayer.h"
#include "Player/SHGPlayerController.h"

ASHGGameMode::ASHGGameMode()
{
	DefaultPawnClass = ASHGPlayer::StaticClass();
	PlayerControllerClass = ASHGPlayerController::StaticClass();
}