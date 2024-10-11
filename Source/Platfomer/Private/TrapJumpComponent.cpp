// Fill out your copyright notice in the Description page of Project Settings.


#include "TrapJumpComponent.h"

// Sets default values for this component's properties
UTrapJumpComponent::UTrapJumpComponent()
{
	PrimaryComponentTick.bCanEverTick = true;
}


// Called when the game starts
void UTrapJumpComponent::BeginPlay()
{
	Super::BeginPlay();

}

void UTrapJumpComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);
}


void UTrapJumpComponent::OnOverlapBegin(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	APlatfomerCharacter* MyCharacter = Cast<APlatfomerCharacter>(OtherActor);
	if (MyCharacter)
	{
		MyCharacter->LaunchCharacter(FVector(0.0f, 0.0f, ForceBoost), false, false);
	}
}

void UTrapJumpComponent::OnOverlapEnd(UPrimitiveComponent* OverlappedComp, AActor* OtherActor,
	UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{
	Super::OnOverlapEnd(OverlappedComp, OtherActor, OtherComp, OtherBodyIndex);
}