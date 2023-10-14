// Fill out your copyright notice in the Description page of Project Settings.


#include "MyHUD.h"
#include "Engine/Canvas.h"
#include "Engine/Texture2D.h"
#include "TextureResource.h"
#include "CanvasItem.h"
#include "UObject/ConstructorHelpers.h"
#include "Blueprint/UserWidget.h"


AMyHUD::AMyHUD()
{
	static ConstructorHelpers::FClassFinder<UUserWidget> HealthBarObj(TEXT("/Game/FirstPerson/HUD/Health_UI"));
	HUDWidgetClass = HealthBarObj.Class;
	
	UE_LOG(LogTemp, Warning, TEXT("Hello2"));
}

void AMyHUD::DrawHUD()
{
	Super::DrawHUD();



}

void AMyHUD::BeginPlay()
{
	Super::BeginPlay();

	
	if (HUDWidgetClass != nullptr)
	{
		
		CurrentWidget = CreateWidget<UUserWidget>(GetWorld(), HUDWidgetClass);
		if (CurrentWidget)
		{
			CurrentWidget->AddToViewport();
		}
	}
}
UUserWidget* AMyHUD::GetWidget(){
	return CurrentWidget;
}
void AMyHUD::RemoveWidget() {
	if (CurrentWidget != nullptr)
	{
		CurrentWidget->RemoveFromViewport();

		CurrentWidget = nullptr;
	}
}