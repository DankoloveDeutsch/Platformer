// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "../PlatfomerGameMode.h"
#include "StartLine.generated.h"

UCLASS()
class PLATFOMER_API AStartLine : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AStartLine();
	
protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	UPROPERTY(EditAnywhere)
	UStaticMeshComponent* StaticMeshComponent;

	virtual void Tick(float DeltaTime) override;
	
	UPROPERTY(EditAnywhere)
	APlatfomerGameMode* MyGameMode;
	
	UFUNCTION()
	void OnStartLineEndOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex);
};
