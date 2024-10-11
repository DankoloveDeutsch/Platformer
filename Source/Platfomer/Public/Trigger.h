// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/TriggerBox.h"
#include "Kismet/GameplayStatics.h"
#include "GameFramework/Actor.h" 
#include "../PlatfomerCharacter.h"
#include "TrapBase.h"
#include "Trigger.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FGameStartTriggerDelegate, double, GameStartTime);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FGameOverTriggerDelegate, bool, bWinLose);
DECLARE_DYNAMIC_MULTICAST_DELEGATE(FTrapsStartDelegate);


UCLASS()
class PLATFOMER_API ATrigger : public ATriggerBox
{
	GENERATED_BODY()
	

public:
	ATrigger();
	
	UFUNCTION()
	void OnOverlapBegin(class AActor* OverlappedActor, class AActor* OtherActor);
	
	UPROPERTY()
	bool bTriggerActivated;

	UPROPERTY(BlueprintCallable)
	FGameOverTriggerDelegate OnGameOver;
	UPROPERTY(BlueprintCallable)
	FGameStartTriggerDelegate OnStart;
	UPROPERTY(Blueprintable)
	FTrapsStartDelegate TrapsStart;

protected:
	virtual void BeginPlay() override;
};
