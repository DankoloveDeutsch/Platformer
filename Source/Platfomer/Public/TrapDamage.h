// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "../PlatfomerCharacter.h"
#include "Kismet/GameplayStatics.h"
#include "TimerManager.h"
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
	bool bCanInflictDamage; // ����� �� ������� ����

	UPROPERTY(EditAnywhere)
	float DamageRate; // ����� ��������� ������� �� ��������� �����
	UPROPERTY(EditAnywhere)
	float DamageAmount; // ���������� ����� ��� ������ �����
	UPROPERTY(EditAnywhere)
	float DamageColdawn; // ����� ����������� �������
	UPROPERTY(EditAnywhere)
	FTimerHandle TimerHandle_Damage;
	UPROPERTY(EditAnywhere)
	FTimerHandle TimerHandle_Reset;

	//APlatfomerCharacter* OverlappingCharacter;
	
	// ���������� �������� �������
	UMaterialInterface* NormalMaterial;

	// ���� ������� �� ����� ���������
	UMaterialInterface* ActivatedMaterial;

	// ���� ������� �� ����� ��������� ����� � �����������
	UMaterialInterface* DamageMaterial;

	UPROPERTY(EditAnywhere)
	APlatfomerCharacter* MyCharacter;

	UFUNCTION()
	void InflictDamage(); // ������� ��������� ����� �������� ���������

	UFUNCTION()
	void ResetTrap(); // ������� ����������� �������

	UFUNCTION()
	void OnOverlap(AActor* MyOverlappedActor, AActor* OtherActor);
	UFUNCTION()
	void OnOverlapEnd(AActor* MyOverlappedActor, AActor* OtherActor);

	
};
