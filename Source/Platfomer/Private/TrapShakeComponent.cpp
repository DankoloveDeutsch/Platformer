// Fill out your copyright notice in the Description page of Project Settings.


#include "TrapShakeComponent.h"



UTrapShakeComponent::UTrapShakeComponent()
{
}

void UTrapShakeComponent::BeginPlay()
{
	Super::BeginPlay();
}

void UTrapShakeComponent::OnOverlapBegin(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	if (OtherActor && OtherActor->IsA(APlatfomerCharacter::StaticClass()))
	{
		ShakePrepare();
	}
}

void UTrapShakeComponent::ShakePrepare()
{
	if (OwnerActor)
	{
		OwnerActor->ChangeMaterialColor(ShakeColor);
		bIsShaking = true;
		InitialRotation = OwnerActor->GetActorRotation();

		GetWorld()->GetTimerManager().SetTimer(ShakeHandler, this, &UTrapShakeComponent::Shake, 0.05f, true);
	}
}

void UTrapShakeComponent::Shake()
{
	if (!OwnerActor) return;

	FRotator ShakeDelta(0.0f, 0.0f, FMath::RandRange(-ShakeIntensity, ShakeIntensity));
	OwnerActor->SetActorRotation(InitialRotation + ShakeDelta);

	ShakeDuration -= 0.05f;

	if (ShakeDuration <= RedFlagDuration)
	{
		OwnerActor->ChangeMaterialColor(DropColor);
	}

	if (ShakeDuration <= 0.0f)
	{
		StopShaking();
	}
}

void UTrapShakeComponent::StopShaking()
{
	OwnerActor->SetActorRotation(InitialRotation);

	if (AActor* Actor = Cast<AActor>(OwnerActor))
	{
		if (UPrimitiveComponent* RootComponent = Actor->FindComponentByClass<UPrimitiveComponent>())
		{
			RootComponent->SetSimulatePhysics(true);
			RootComponent->SetCollisionResponseToAllChannels(ECR_Ignore);
			
	
			GetWorld()->GetTimerManager().SetTimer(DestroyHandler, this, &UTrapShakeComponent::SelfDestroy, 1.0f, false, 3.0f);
		}
	}
}

void UTrapShakeComponent::SelfDestroy()
{
	if (OwnerActor)
	{
		OwnerActor->Destroy();
	}
}
