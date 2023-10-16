// Copyright Epic Games, Inc. All Rights Reserved.

#include "PlatfomerGameMode.h"
#include "PlatfomerCharacter.h"
#include "MyHUD.h"
#include "Kismet/GameplayStatics.h"
#include "Blueprint/WidgetBlueprintLibrary.h"
#include "UObject/ConstructorHelpers.h"

APlatfomerGameMode::APlatfomerGameMode()
	: Super()
{
	// set default pawn class to our Blueprinted character
	static ConstructorHelpers::FClassFinder<APawn> PlayerPawnClassFinder(TEXT("/Game/FirstPerson/Blueprints/BP_FirstPersonCharacter"));
	DefaultPawnClass = PlayerPawnClassFinder.Class;
	bStopTick = false;
	PrimaryActorTick.bCanEverTick = true;
	LevelTime = 0.0f;

}
void APlatfomerGameMode::BeginPlay()
{
	Super::BeginPlay();

	SetCurrentState(EGamePlayState::EPlaying);
	ChangeMenuWidget(MyHUDClass);

	MyCharacter = Cast<APlatfomerCharacter>(UGameplayStatics::GetPlayerPawn(this, 0));
}

void APlatfomerGameMode::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	if (bStopTick)
	{
		
		return;
	};

	if (MyCharacter)
	{
		if (MyCharacter->GetHealth()<=0.0f || MyCharacter->GetActorLocation().Z<= -100.0f)
		{
			SetCurrentState(EGamePlayState::EGameOver);
		}
	}
}
// Запустить обработку событий
void APlatfomerGameMode::StartTick() {
	bStopTick = false;
	PlayerController->bShowMouseCursor = false;
}
// Метод смены пользовательского виджета
void  APlatfomerGameMode::ChangeMenuWidget(TSubclassOf<UUserWidget> NewWidgetClass)
{
	if (CurrentWidget != nullptr)
	{
		CurrentWidget->RemoveFromViewport();

		CurrentWidget = nullptr;
	}
	if (NewWidgetClass != nullptr)
	{

		CurrentWidget = CreateWidget<UUserWidget>(GetWorld()->GetFirstPlayerController(), NewWidgetClass);

		if (CurrentWidget != nullptr)
		{
			CurrentWidget->AddToViewport();
			
		}
	}
}
// Вернуть текущее состояние игры
EGamePlayState APlatfomerGameMode::GetCurrentState() const
{
	return CurrentState;
}
// Изменить состояние игры
void APlatfomerGameMode::SetCurrentState(EGamePlayState NewState)
{
	CurrentState = NewState;
	HandleNewState(CurrentState);
}
// Применить логику нового состояния игры, установленного SetCurrentState()
void APlatfomerGameMode::HandleNewState(EGamePlayState NewState)
{
	switch (NewState)
	{
	case EGamePlayState::EPlaying:
	{
	}
	break;
	// Unknown/default state
	case EGamePlayState::EGameOver:
	{
		bStopTick = true;
		ChangeMenuWidget(LoserWidgetClass);
		GetWorldTimerManager().ClearTimer(TimerHandle);

		UWorld* World = GetWorld();

		PlayerController = World->GetFirstPlayerController();
	
		PlayerController->bShowMouseCursor = true;

		
	}
	break;
	default:
	case EGamePlayState::EWin:
	{
		bStopTick = true;
		ChangeMenuWidget(WinnerWidgetClass);
		GetWorldTimerManager().ClearTimer(TimerHandle);

		UWorld* World = GetWorld();

		PlayerController = World->GetFirstPlayerController();

		PlayerController->bShowMouseCursor = true;
	}
	break;
	}
}
// Вернуть значение таймера для отображения в пользовательском виджете
float APlatfomerGameMode::GetTimer() {
	return LevelTime;
}

void APlatfomerGameMode::UpdateLevelTime(){
	LevelTime += 0.01f;
}
void  APlatfomerGameMode::StartTimer(){
		GetWorldTimerManager().SetTimer(TimerHandle, this, &APlatfomerGameMode::UpdateLevelTime, 0.01f, true);
}