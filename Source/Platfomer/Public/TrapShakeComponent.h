// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "TrapBaseComponent.h"
#include "TrapBase.h"
#include "../PlatfomerCharacter.h"
#include "TimerManager.h"
#include "Components/PrimitiveComponent.h"
#include "TrapShakeComponent.generated.h"

/**
 * 
 */
UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class PLATFOMER_API UTrapShakeComponent : public UTrapBaseComponent
{
	GENERATED_BODY()
	
public:
	UTrapShakeComponent();

	FTimerHandle ShakeHandler;
	FTimerHandle DestroyHandler;
	
	UPROPERTY()
	bool bIsShaking;
	
	UPROPERTY(EditAnywhere, Category="Traps Settings|Shake")
	float ShakeDuration = 5.f;
	UPROPERTY(EditAnywhere, Category="Traps Settings|Shake")
	float ShakeIntensity = 5.f;
	UPROPERTY(EditAnywhere, Category="Traps Settings|Shake")
	float RedFlagDuration = 1.f;
	UPROPERTY()
	FRotator InitialRotation;

	UFUNCTION()
	void ShakePrepare();
	UFUNCTION()
	void Shake();
	UFUNCTION()
	void StopShaking();
	UFUNCTION()
	void SelfDestroy();
	
	UPROPERTY(EditAnywhere, Category="Traps Settings|Shake")
	FLinearColor BaseColor = FLinearColor::Gray;
	UPROPERTY(EditAnywhere, Category="Traps Settings|Shake")
	FLinearColor ShakeColor = FLinearColor::Yellow;
	UPROPERTY(EditAnywhere, Category="Traps Settings|Shake")
	FLinearColor DropColor = FLinearColor::Red;

	virtual void BeginPlay() override;
	virtual void OnOverlapBegin(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult) override;

	
};
