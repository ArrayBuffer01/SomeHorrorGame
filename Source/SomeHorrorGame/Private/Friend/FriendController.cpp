// Fill out your copyright notice in the Description page of Project Settings.


#include "Friend/FriendController.h"
#include "Friend/BlackboardKeys.h"
#include "BehaviorTree/BehaviorTree.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "Player/SHGPlayer.h"
#include "Perception/AIPerceptionComponent.h"
#include "Perception/AISenseConfig_Sight.h"
#include "Perception/AISenseConfig_Hearing.h"


AFriendController::AFriendController()
{
	CurrentState = EFriendState::None;

	PerceptionComp = CreateDefaultSubobject<UAIPerceptionComponent>(TEXT("PerceptionComp"));
	HearingConfig = CreateDefaultSubobject<UAISenseConfig_Hearing>(TEXT("HearingConfig"));
	SightConfig = CreateDefaultSubobject<UAISenseConfig_Sight>(TEXT("SightConfig"));

	SightConfig->SightRadius = 2000.f;
	SightConfig->LoseSightRadius = 2500.f;
	SightConfig->PeripheralVisionAngleDegrees = 90.f;
	SightConfig->SetMaxAge(2.f);
	SightConfig->DetectionByAffiliation.bDetectEnemies = true;
	SightConfig->DetectionByAffiliation.bDetectNeutrals = true;
	SightConfig->DetectionByAffiliation.bDetectFriendlies = true;

	HearingConfig->HearingRange = 1500.f;
	HearingConfig->SetMaxAge(1.f);
	HearingConfig->DetectionByAffiliation = SightConfig->DetectionByAffiliation;

	PerceptionComp->SetDominantSense(SightConfig->GetSenseImplementation());

	PerceptionComp->ConfigureSense(*SightConfig);
	PerceptionComp->ConfigureSense(*HearingConfig);
}
void AFriendController::BeginPlay()
{
	Super::BeginPlay();
	if (PerceptionComp)
	{
		PerceptionComp->OnTargetPerceptionUpdated.AddDynamic(this, &AFriendController::OnTargetPerceptionUpdated);
	}
	
	GetBlackboardComponent()->SetValueAsEnum(BBK_CURRENTSTATE, (uint8)CurrentState);
}

void AFriendController::SetState(EFriendState State)
{
	if (CurrentState != State)
	{
		CurrentState = State;
		OnStateChange.Broadcast(State);
		
		GetBlackboardComponent()->SetValueAsEnum(BBK_CURRENTSTATE, (uint8)State);
	}
}

void AFriendController::SetLastPlayerLocation(FVector Location)
{
	LastPlayerLocation = Location;
	GetBlackboardComponent()->SetValueAsVector(BKK_LASTPLAYERLOCATION, Location);
}

void AFriendController::OnPossess(APawn* InPawn)
{
	Super::OnPossess(InPawn);

	if (BehaviorTree)
	{
		RunBehaviorTree(BehaviorTree);
	}
}

void AFriendController::OnTargetPerceptionUpdated(AActor* Actor, FAIStimulus Stimulus)
{
	if (!Actor)
		return;

	GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Green, FString::Printf(TEXT("Actor detected: %s"), *Actor->GetName()));

	if (Actor->IsA(ASHGPlayer::StaticClass()))
	{
		GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Green, FString::Printf(TEXT("PLAYER DETECTED: %s, Succ Sensed: %d"), *Actor->GetName(), Stimulus.WasSuccessfullySensed()));
		GetBlackboardComponent()->SetValueAsBool(BBK_CANSEEPLAYER, Stimulus.WasSuccessfullySensed());
		GetBlackboardComponent()->SetValueAsObject(BBK_TARGETPLAYER, Actor);

		if (!Stimulus.WasSuccessfullySensed())
		{
			SetLastPlayerLocation(Stimulus.StimulusLocation);
		}
		if (CurrentState != EFriendState::None && CurrentState != EFriendState::Chasing && Stimulus.WasSuccessfullySensed())
		{
			SetState(EFriendState::Chasing);
		}
	}
}
