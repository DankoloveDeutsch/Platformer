// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "../PlatfomerCharacter.h"
#include "Components/StaticMeshComponent.h"
#include "TrapDamage.generated.h"

UCLASS()
class PLATFOMER_API ATrapDamage : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ATrapDamage();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	UPROPERTY(EditAnywhere)
	UStaticMeshComponent* StaticMeshComponent;

	UPROPERTY(EditAnywhere)
	bool bCanInflictDamage; // Можно ли нанести урон

	UPROPERTY(EditAnywhere)
	float DamageRate; // Время активации ловушки до нанесения урона
	UPROPERTY(EditAnywhere)
	float DamageAmount; // Количество урона при каждом ударе
	UPROPERTY(EditAnywhere)
	float DamageColdawn; // Время перезарядки ловушки
	UPROPERTY(EditAnywhere)
	FTimerHandle TimerHandle_Damage;
	UPROPERTY(EditAnywhere)
	FTimerHandle TimerHandle_Reset;

	// Нормальный материал объекта
	UMaterialInterface* NormalMaterial;

	// Цвет ловушки во время активации
	UMaterialInterface* ActivatedMaterial;

	// Цвет ловушки во время нанесения урона и перезарядки
	UMaterialInterface* DamageMaterial;

	UPROPERTY(EditAnywhere)
	APlatfomerCharacter* MyCharacter;

	UFUNCTION()
	void InflictDamage(); // Функция нанесения урона ловушкой персонажу

	UFUNCTION()
	void ResetTrap(); // Функция перезарядки ловушки

	UFUNCTION()
	void OnOverlap(AActor* MyOverlappedActor, AActor* OtherActor);
	UFUNCTION()
	void OnOverlapEnd(AActor* MyOverlappedActor, AActor* OtherActor);

	
};
