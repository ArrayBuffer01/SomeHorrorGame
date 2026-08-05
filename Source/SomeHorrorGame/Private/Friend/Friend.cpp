// Fill out your copyright notice in the Description page of Project Settings.


#include "Friend/Friend.h"
#include "Friend/FriendController.h"

// Sets default values
AFriend::AFriend()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	AIControllerClass = AFriendController::StaticClass();
}

// Called when the game starts or when spawned
void AFriend::BeginPlay()
{
	Super::BeginPlay();
}

// Called every frame
void AFriend::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

// Called to bind functionality to input
void AFriend::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}