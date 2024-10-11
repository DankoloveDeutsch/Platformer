// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "GameHUD.generated.h"

/**
 * 
 */
UCLASS()
class PLATFOMER_API UGameHUD : public UUserWidget
{
	GENERATED_BODY()
public:
	virtual void NativeConstruct() override;

	UPROPERTY(EditAnywhere, meta=(BindWidget))
	class UProgressBar* HealthBar;

	UFUNCTION(BlueprintCallable, Category = "Health")
	void HandleHealthUpdate(float UpdHealth,float UpdMaxHealth);

};
