// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "../PlatfomerCharacter.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "TrapBaseComponent.h"
#include "TrapJumpComponent.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class PLATFOMER_API UTrapJumpComponent : public UTrapBaseComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UTrapJumpComponent();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

	virtual void OnOverlapBegin(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);
	virtual void OnOverlapEnd(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex);
	

	UPROPERTY(EditAnywhere, Category="Traps Settings|Jump")
	float ForceBoost = 1000.0f;

	UPROPERTY(EditAnywhere, Category="Traps Settings|Jump")
	FLinearColor BaseColor = FLinearColor::Gray;

	UPROPERTY(EditAnywhere, Category="Traps Settings|Jump")
	FLinearColor ActiveColor = FLinearColor::Green;
};
