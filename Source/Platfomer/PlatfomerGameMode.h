// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "PlatfomerCharacter.h"
#include "public/MyHUD.h"
#include "PlatfomerPlayerController.h"
#include "Blueprint/UserWidget.h"
#include "GameFramework/PlayerController.h"
#include "PlatfomerGameMode.generated.h"


UCLASS(minimalapi)
class APlatfomerGameMode : public AGameModeBase
{
	GENERATED_BODY()
protected:

public:
	APlatfomerGameMode();

	
	virtual void BeginPlay() override;
	
	virtual void Tick(float DeltaTime) override;
	
	UFUNCTION(BlueprintCallable)
	void GameOver(bool bWonGame);

	UPROPERTY(BlueprintReadOnly)
	double GameStartTime;

	UFUNCTION()
	void SetGameStartTime(double time);

	UPROPERTY(BlueprintReadOnly)
	double GameEndTime;

	UPROPERTY(EditAnywhere, Category="UI")
	TSubclassOf<class UGameHUD> PlayerHUDClass;
	UPROPERTY()
	UGameHUD* PlayerHUD;


	UPROPERTY(EditAnywhere, Category="UI")
	TSubclassOf<class UGameOver> GameOverHUDClass;

	UPROPERTY()
	UGameOver* GameOverHUD;

	void DeleteHUD();

};



