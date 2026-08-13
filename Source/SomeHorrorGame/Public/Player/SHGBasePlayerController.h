// SomeHorrorGame TM

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "SHGBasePlayerController.generated.h"

class USHGGameInstance;
class UInputMappingContext;


/**
 * 
 */
UCLASS()
class SOMEHORRORGAME_API ASHGBasePlayerController : public APlayerController
{
	GENERATED_BODY()
public:
	UPROPERTY(BlueprintReadOnly)
	TObjectPtr<USHGGameInstance> GameInstance;

	UPROPERTY(EditAnywhere, Category = "Input")
	TObjectPtr<UInputMappingContext> InputMapping;
public:
	void BeginPlay() override;
};
