// SomeHorrorGame TM


#include "Player/SHGBasePlayerController.h"
#include "EnhancedInputSubsystems.h"
#include "Game/SHGGameInstance.h"

void ASHGBasePlayerController::BeginPlay()
{
	ULocalPlayer* LocalPlayer = GetLocalPlayer();

	if (!LocalPlayer)
		return;

	UEnhancedInputLocalPlayerSubsystem* Subsystem = LocalPlayer->GetSubsystem<UEnhancedInputLocalPlayerSubsystem>();

	if (!Subsystem)
		return;


	// Clear mappings
	Subsystem->ClearAllMappings();

	// Add mapping context
	FModifyContextOptions ModifyOptions = FModifyContextOptions();
	ModifyOptions.bNotifyUserSettings = true;

	Subsystem->AddMappingContext(InputMapping, 0, ModifyOptions);
	
	GameInstance = GetGameInstance<USHGGameInstance>();

	GameInstance->RestoreInputSettings();

	Super::BeginPlay();
}