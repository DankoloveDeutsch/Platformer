// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "PlatfomerCharacter.h"
#include "MyHUD.h"
#include "PlatfomerPlayerController.h"
#include "Blueprint/UserWidget.h"
#include "GameFramework/PlayerController.h"
#include "PlatfomerGameMode.generated.h"

UENUM()
enum class EGamePlayState
{
	ENewGame,
	EPlaying,
	EGameOver,
	EWin
};

UCLASS(minimalapi)
class APlatfomerGameMode : public AGameModeBase
{
	GENERATED_BODY()
protected:


	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "UMG Game")
	TSubclassOf<UUserWidget> WinnerWidgetClass;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "UMG Game")
	TSubclassOf<UUserWidget> LoserWidgetClass;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "UMG Game")
	TSubclassOf<UUserWidget> MyHUDClass;

	AMyHUD* HudWidget;
	/** The widget instance that we are using as our menu. */
	UPROPERTY()
	UUserWidget* CurrentWidget;

public:
	APlatfomerGameMode();
	APlayerController* PlayerController;
	virtual void BeginPlay() override;
	
	virtual void Tick(float DeltaTime) override;

	bool bStopTick;
	APlatfomerCharacter* MyCharacter;

	UFUNCTION(BlueprintCallable, Category = "UMG Game")
	void ChangeMenuWidget(TSubclassOf<UUserWidget> NewWidgetClass);

	UFUNCTION(BlueprintPure, Category = "Health")
	EGamePlayState GetCurrentState() const;

	UFUNCTION(BlueprintCallable, Category = "Health")
	void StartTick();
	/** Sets a new playing state */
	void SetCurrentState(EGamePlayState NewState);

	UPROPERTY(EditAnywhere)
	FTimerHandle TimerHandle; // Таймер прохождения

	UFUNCTION(BlueprintCallable, Category = "Timer")
	float GetTimer();

	UFUNCTION(BlueprintCallable, Category = "Timer")
	void UpdateLevelTime();

	UPROPERTY(EditAnywhere)
	float LevelTime;

	void StartTimer();
private: 
	/**Keeps track of the current playing state */
	EGamePlayState CurrentState;

	/**Handle any function calls that rely upon changing the playing state of our game */
	void HandleNewState(EGamePlayState NewState);
};



