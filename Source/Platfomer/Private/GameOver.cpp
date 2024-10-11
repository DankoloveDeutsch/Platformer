// Fill out your copyright notice in the Description page of Project Settings.


#include "GameOver.h"
#include "TrapBase.h"
#include "Components/TextBlock.h"
#include "Kismet/GameplayStatics.h"

void UGameOver::RestartLevel()
{
	APlayerController* PlayerController = UGameplayStatics::GetPlayerController(GetWorld(),0);
	if (PlayerController)
	{
		PlayerController->bShowMouseCursor = false;
		PlayerController->bEnableClickEvents = false;
		PlayerController->SetInputMode(FInputModeGameOnly());

		TArray<AActor*> TrapBases;
		UGameplayStatics::GetAllActorsOfClass(GetWorld(),ATrapBase::StaticClass(),TrapBases);
		for (AActor* Traps: TrapBases)
		{
			ATrapBase* Trap = Cast<ATrapBase>(Traps);
			if (Trap)
			{
				Trap->ResetTimers();
			}
		}
		UGameplayStatics::OpenLevel(GetWorld(), "FirstPersonMap", false);
	}
	else
	{
		UE_LOG(LogTemp,Error,TEXT("RestartLevel() in GameOver.cpp error finding playercontroller/gamemode "));
	}
}

void UGameOver::SetGameDuration(double GameStarTime, double GameEndtime)
{
	double DurationCount = GameEndtime - GameStarTime;
	Duration->SetText(FText::Format(FText::FromString("{0}{1}"),FText::FromString(TEXT("Твоё время: ")),FText::AsNumber(DurationCount)));
}

void UGameOver::SetWinLose(bool bWin)
{
	if (bWin)
	{
		WinLose->SetText(FText::FromString(TEXT("ПОБЕДА!")));
	}
	if (!bWin)
	{
		WinLose->SetText((FText::FromString(TEXT("ПОТРАЧЕНО"))));
	}
}
