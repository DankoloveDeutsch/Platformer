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
	bool WindChange; // ������� �� ����������� �����?
	UPROPERTY(EditAnywhere)
	float WindForce; // ���� �����
	UPROPERTY(EditAnywhere)
	float ChangeCooldown; // ����� ����� �����������
	UPROPERTY(EditAnywhere)
	FTimerHandle TimerHandle_Change;

	// ���������� �������� �������
	UMaterialInterface* NormalMaterial;

	// ���� ������� �� ����� ���������
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
	void ChangeDirection(); // ������� ����� �����������

	UFUNCTION()
	void WindAction(float DeltaTime); // ������� ����������� �������

	UFUNCTION()
	void OnTrapOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);
	UFUNCTION()
	void OnTrapEndOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex);

};
