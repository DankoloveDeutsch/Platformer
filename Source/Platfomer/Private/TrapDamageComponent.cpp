
#include "TrapDamageComponent.h"


UTrapDamageComponent::UTrapDamageComponent()
{
	PrimaryComponentTick.bCanEverTick = true;
	bIsTrapCooldown = false;
}

void UTrapDamageComponent::BeginPlay()
{
	Super::BeginPlay();
}


void UTrapDamageComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);
}

void UTrapDamageComponent::OnOverlapBegin(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	if (OverlappedComp == InteractCollision)
	{
		if (bIsTrapCooldown == false)
		{
			DamagePrepare(OtherActor);
			SetTrapCooldown(OtherActor);
		}
	}
}

void UTrapDamageComponent::OnOverlapEnd(UPrimitiveComponent* OverlappedComp, AActor* OtherActor,
	UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{
	Super::OnOverlapEnd(OverlappedComp, OtherActor, OtherComp, OtherBodyIndex);
}

void UTrapDamageComponent::DamagePrepare(AActor* OtherActor)
{
	if(InteractCollision->IsOverlappingActor(OtherActor))
	{
		OwnerActor->ChangeMaterialColor(ActiveColor);

		auto Lambda = [this, OtherActor]()
		{
			Damage(OtherActor);
		};

		GetWorld()->GetTimerManager().SetTimer(DamageTimerHandle, Lambda, TimeForDamage, false);
	}
}

void UTrapDamageComponent::Damage(AActor* OtherActor)
{
	OwnerActor->ChangeMaterialColor(DamageColor);

	TArray<AActor*> OverlappingActors;
	InteractCollision->GetOverlappingActors(OverlappingActors);
	for (AActor* Actor : OverlappingActors)
	{
		APlatfomerCharacter* Character = Cast<APlatfomerCharacter>(Actor);
		if (Character)
		{
			FDamageEvent DamageEvent;
			Character->UpdateHealth(-TrapDamage);
		}
	}

	GetWorld()->GetTimerManager().SetTimer(RedColorTimerHandle, this, &UTrapDamageComponent::ResetMaterial, MaterialResetTime, false);

	if(InteractCollision->IsOverlappingActor(OtherActor) && bIsTrapCooldown == false)
	{
		auto Lambda = [this, OtherActor]()
		{
			DamagePrepare(OtherActor);
		};
			
		GetWorld()->GetTimerManager().SetTimer(DamageCooldownHandle, Lambda, 0, true);
	}
	
}

void UTrapDamageComponent::ResetMaterial()
{
	OwnerActor->ChangeMaterialColor(BaseColor);
}


void UTrapDamageComponent::SetTrapCooldown(AActor* OtherActor)
{
	bIsTrapCooldown = true;
	
	auto Lambda = [this, OtherActor]()
	{
		ResetTrapCooldown(OtherActor);
	};
	
	GetWorld()->GetTimerManager().SetTimer(CooldownHandle, Lambda,CooldownDuration, false);
}

void UTrapDamageComponent::ResetTrapCooldown(AActor* OtherActor)
{
	bIsTrapCooldown = false;

	if (OtherActor && OtherActor->IsA<APlatfomerCharacter>() && InteractCollision->IsOverlappingActor(OtherActor))
	{
		DamagePrepare(OtherActor);
		SetTrapCooldown(OtherActor); 
	}
}

void UTrapDamageComponent::ResetTimer()
{
	GetWorld()->GetTimerManager().ClearTimer(DamageTimerHandle);
	GetWorld()->GetTimerManager().ClearTimer(RedColorTimerHandle);
	GetWorld()->GetTimerManager().ClearTimer(DamageCooldownHandle);
	GetWorld()->GetTimerManager().ClearTimer(CooldownHandle);
}
