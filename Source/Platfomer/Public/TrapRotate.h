// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "TrapRotate.generated.h"

UCLASS()
class PLATFOMER_API ATrapRotate : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ATrapRotate();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	UPROPERTY(VisibleAnywhere)
	UStaticMeshComponent* TrapMesh;
	
	UPROPERTY(EditDefaultsOnly, Category = "Trap")
	UMaterialInterface* NormalMaterial;
	
	UFUNCTION()
	void RotateTrap(float DeltaTime);
	
	UPROPERTY(EditAnywhere)
	float  RotationSpeed;
};
