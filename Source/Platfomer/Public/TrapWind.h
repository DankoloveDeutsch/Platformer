// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "../PlatfomerCharacter.h"
#include "TrapWind.generated.h"

UCLASS()
class PLATFOMER_API ATrapWind : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ATrapWind();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	void Tick(float DeltaTime) override;


	UPROPERTY(EditAnywhere)
	UStaticMeshComponent* StaticMeshComponent;

	UPROPERTY(EditAnywhere)
	bool WindChange; // Сменить ли направление ветра?
	UPROPERTY(EditAnywhere)
	float WindForce; // Сила ветра
	UPROPERTY(EditAnywhere)
	float ChangeCooldown; // Время смены направления
	UPROPERTY(EditAnywhere)
	FTimerHandle TimerHandle_Change;

	// Нормальный материал объекта
	UMaterialInterface* NormalMaterial;

	// Цвет ловушки во время активации
	UMaterialInterface* ActivatedMaterial;


	UPROPERTY(EditAnywhere)
	APlatfomerCharacter* MyCharacter;

	UPROPERTY(EditAnywhere)
	FTimerHandle WindChangeTimer;

	UPROPERTY()
	FVector WindDirection;

	void EnableWind();
	void DisableWind();

	UFUNCTION()
	void ChangeDirection(); // Функция смены направления

	UFUNCTION()
	void WindAction(float DeltaTime); // Функция перезарядки ловушки

	UFUNCTION()
	void OnTrapOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);
	UFUNCTION()
	void OnTrapEndOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex);

};
