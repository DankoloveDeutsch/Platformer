// Copyright Epic Games, Inc. All Rights Reserved.


#include "PlatfomerPlayerController.h"
#include "EnhancedInputSubsystems.h"

void APlatfomerPlayerController::BeginPlay()
{
	Super::BeginPlay();

	// get the enhanced input subsystem
	if (UEnhancedInputLocalPlayerSubsystem* Subsystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(GetLocalPlayer()))
	{
		// add the mapping context so we get controls
		Subsystem->AddMappingContext(InputMappingContext, 0);
		//APlatfomerPlayerController::SetInputMode(FInputModeGameAndUI());
		
		UE_LOG(LogTemp, Warning, TEXT("BeginPlay"));
	}
}
void APlatfomerPlayerController::SetinputUIOnly() {
	SetInputMode(FInputModeUIOnly());
}
