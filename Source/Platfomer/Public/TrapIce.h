// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "../PlatfomerCharacter.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "Components/StaticMeshComponent.h"
#include "TrapIce.generated.h"

UCLASS()
class PLATFOMER_API ATrapIce : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ATrapIce();
    virtual ~ATrapIce();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;
	
	UPROPERTY(VisibleAnywhere)
	UStaticMeshComponent* StaticMeshComponent;

	UPROPERTY(EditDefaultsOnly)
	UMaterialInterface* NormalMaterial;

	// ���� ������� �� ����� ���������
	UMaterialInterface* ActivatedMaterial;
	UPROPERTY(EditAnywhere)
	APlatfomerCharacter* MyCharacter;

	
	UFUNCTION()
	void OnOverlap(AActor* MyOverlappedActor, AActor* OtherActor);
	UFUNCTION()
	void OnOverlapEnd(AActor* MyOverlappedActor, AActor* OtherActor);
};
