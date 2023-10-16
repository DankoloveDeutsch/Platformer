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

	UPROPERTY()
	UUserWidget* CurrentWidget;

public:
	APlatfomerGameMode();

	
	virtual void BeginPlay() override;
	
	virtual void Tick(float DeltaTime) override;

	UPROPERTY(EditAnywhere)
	bool bStopTick;

	APlatfomerCharacter* MyCharacter;
	APlayerController* PlayerController;

	UFUNCTION(BlueprintCallable, Category = "UMG Game")
	void ChangeMenuWidget(TSubclassOf<UUserWidget> NewWidgetClass);

	UFUNCTION(BlueprintPure, Category = "Health")
	EGamePlayState GetCurrentState() const;

	UFUNCTION(BlueprintCallable, Category = "Health")
	void StartTick();

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

	EGamePlayState CurrentState;

	void HandleNewState(EGamePlayState NewState);
};



