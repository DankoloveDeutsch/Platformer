// Copyright Epic Games, Inc. All Rights Reserved.

#include "PlatfomerGameMode.h"
#include "PlatfomerCharacter.h"
#include "GameHUD.h"
#include "Trigger.h"
#include "Kismet/GameplayStatics.h"
#include "Blueprint/WidgetBlueprintLibrary.h"
#include "Blueprint/UserWidget.h"
#include "GameOver.h"

#include "UObject/ConstructorHelpers.h"

APlatfomerGameMode::APlatfomerGameMode()
{
	// set default pawn class to our Blueprinted character
	static ConstructorHelpers::FClassFinder<APawn> PlayerPawnClassFinder(TEXT("/Game/FirstPerson/Blueprints/BP_FirstPersonCharacter"));
	if (PlayerPawnClassFinder.Class != NULL)
	{
		DefaultPawnClass = PlayerPawnClassFinder.Class;
	}

	PlayerHUDClass = nullptr;
	PlayerHUD = nullptr;

	GameOverHUDClass = nullptr;
	GameOverHUD = nullptr;

}
void APlatfomerGameMode::BeginPlay()
{
	Super::BeginPlay();

	APlayerController* Controller = UGameplayStatics::GetPlayerController(GetWorld(), 0);
	if (Controller)
	{
		APlatfomerCharacter* Player = Cast<APlatfomerCharacter>(Controller->GetPawn());
		if (Player)
		{
			Player->OnGameOver.AddDynamic(this,&APlatfomerGameMode::GameOver);
		}
	}

	TArray<AActor*> Triggers;
	UGameplayStatics::GetAllActorsOfClass(GetWorld(),ATrigger::StaticClass(),Triggers);
	for (AActor* Actor : Triggers)
	{
		ATrigger* Trigger = Cast<ATrigger>(Actor);
		if(Trigger && Trigger->ActorHasTag("Win") || Trigger->ActorHasTag("Lose"))
		{
			Trigger->OnGameOver.AddDynamic(this,&APlatfomerGameMode::GameOver);
		}
		else if (Trigger && Trigger->ActorHasTag("Start"))
		{
			Trigger->OnStart.AddDynamic(this,&APlatfomerGameMode::SetGameStartTime);
		}
	}

	if(PlayerHUDClass)
	{
		APlayerController* FPC = UGameplayStatics::GetPlayerController(GetWorld(),0);
		check(FPC);
		PlayerHUD = CreateWidget<UGameHUD>(FPC, PlayerHUDClass);
		check(PlayerHUD);
		PlayerHUD->AddToPlayerScreen();

	}
	
}

void APlatfomerGameMode::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	
}

void  APlatfomerGameMode::GameOver(bool bWonGame)
{
	APlayerController* PlayerController = UGameplayStatics::GetPlayerController(GetWorld(),0);
	if (PlayerController)
	{
		PlayerController->bShowMouseCursor = true;
		PlayerController->bEnableClickEvents = true;
		PlayerController->SetInputMode(FInputModeUIOnly());
		GameEndTime = UGameplayStatics::GetRealTimeSeconds(GetWorld());
		
		if (GameOverHUDClass)
		{
			GameOverHUD = CreateWidget<UGameOver>(GetWorld(),GameOverHUDClass);
			check(GameOverHUD);

			UGameplayStatics::SetGamePaused(GetWorld(),true);
			
			GameOverHUD->AddToPlayerScreen();
			
			GameOverHUD->SetGameDuration(GameStartTime,GameEndTime);
			GameOverHUD->SetWinLose(bWonGame);
		}
	}
}


void APlatfomerGameMode::SetGameStartTime(double time)
{
	GameStartTime = time;
}

void APlatfomerGameMode::DeleteHUD()
{
	GameOverHUD->SetVisibility(ESlateVisibility::Hidden);
}
