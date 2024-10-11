#include "TrapWindComponent.h"


UTrapWindComponent::UTrapWindComponent()
{
}


void UTrapWindComponent::BeginPlay()
{
	Super::BeginPlay();

}



void UTrapWindComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);
}

void UTrapWindComponent::OnOverlapBegin(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	if (OverlappedComp == InteractCollision)
	{
		Wind(OtherActor);
	}
}

void UTrapWindComponent::OnOverlapEnd(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{
	Super::OnOverlapEnd(OverlappedComp, OtherActor, OtherComp, OtherBodyIndex);
	GetWorld()->GetTimerManager().ClearTimer(WindTimerHandle);
	GetWorld()->GetTimerManager().ClearTimer(WindChangeHandle);
	OwnerActor->ChangeMaterialColor(BaseColor);
}

void UTrapWindComponent::Wind(AActor* OtherActor)
{
	OwnerActor->ChangeMaterialColor(ActiveColor);
	
	auto WindApplyLambda = [this, OtherActor]()
	{
		WindApply(OtherActor);
	};
	
	GetWorld()->GetTimerManager().SetTimer(WindChangeHandle,WindApplyLambda,WindChangeRate,true, 0.f);
}

void UTrapWindComponent::WindApply(AActor* OtherActor)
{
	RandomX = FMath::FRandRange(-1.0f, 1.0f);
    RandomY = FMath::FRandRange(-1.0f, 1.0f);

	WindPower = FMath::FRandRange(MinWindPower, MaxWindPower);


	FVector WindDirection = FVector(RandomX*WindPower, RandomY*WindPower, 0.f);
	auto WindChangeLambda = [this, OtherActor, WindDirection]()
	{
		WindChange(OtherActor,WindDirection);
	};
	
	GetWorld()->GetTimerManager().ClearTimer(WindTimerHandle);
	GetWorld()->GetTimerManager().SetTimer(WindTimerHandle,WindChangeLambda,WindPressure*GetWorld()->GetDeltaSeconds(),true);
}

void UTrapWindComponent::WindChange(AActor* OtherActor, FVector WindDirection)
{
	FVector TargetLocation = OtherActor->GetActorLocation() + WindDirection;
	FVector newLocation = FMath::VInterpTo(OtherActor->GetActorLocation(), TargetLocation, GetWorld()->GetDeltaSeconds(), 1);
	OtherActor->SetActorLocation(newLocation);
}

void UTrapWindComponent::ResetTimer()
{
	GetWorld()->GetTimerManager().ClearTimer(WindTimerHandle);
	GetWorld()->GetTimerManager().ClearTimer(WindChangeHandle);
}