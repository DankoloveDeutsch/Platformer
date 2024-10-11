// Fill out your copyright notice in the Description page of Project Settings.


#include "GameHUD.h"
#include "../PlatfomerCharacter.h"
#include "Components/ProgressBar.h"
#include "Kismet/GameplayStatics.h"


void UGameHUD::NativeConstruct()
{
	Super::NativeConstruct();

	APlayerController* Controller = UGameplayStatics::GetPlayerController(GetWorld(),0);
	APlatfomerCharacter* Player = Cast<APlatfomerCharacter>(Controller);
	if (Player)
	{
		Player->OnHealthUpdated.AddDynamic(this,&UGameHUD::HandleHealthUpdate);
		
	}
}

void UGameHUD::HandleHealthUpdate(float UpdHealth,float UpdMaxHealth)
{
	if (HealthBar)
	{
		HealthBar->SetPercent(UpdHealth/UpdMaxHealth);
	}
}