// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/HUD.h"
#include "MyHUD.generated.h"

/**
 * 
 */
UCLASS()
class PLATFOMER_API AMyHUD : public AHUD
{
	GENERATED_BODY()
	
public:

	AMyHUD();
	/** Primary draw call for the HUD */
	virtual void DrawHUD() override;

	virtual void BeginPlay() override;

	UPROPERTY(EditAnywhere, Category = "Health")
	TSubclassOf<class UUserWidget> HUDWidgetClass;

	UFUNCTION()
	UUserWidget* GetWidget();
	
	UFUNCTION()
	void RemoveWidget();

	UPROPERTY(EditAnywhere, Category = "Health")
	class UUserWidget* CurrentWidget;
private:

	

	
};
