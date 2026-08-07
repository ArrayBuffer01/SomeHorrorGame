// Fill out your copyright notice in the Description page of Project Settings.


#include "SettingsSave.h"

USettingsSave::USettingsSave()
{
	UE_LOG(LogTemp, Warning, TEXT("Master: %f"), SettingsData.AudioSettings.MasterVolume);
}