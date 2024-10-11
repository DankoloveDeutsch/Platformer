#pragma once

#include "CoreMinimal.h"
#include "TrapBase.h"
#include "Components/BoxComponent.h"
#include "../PlatfomerCharacter.h"
#include "Engine/DamageEvents.h"
#include "TrapBaseComponent.h"
#include "TrapDamageComponent.generated.h"

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class PLATFOMER_API UTrapDamageComponent : public UTrapBaseComponent
{
	GENERATED_BODY()

public:	
	UTrapDamageComponent();
	
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

	virtual void OnOverlapBegin(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);
	virtual void OnOverlapEnd(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex);
	
	UFUNCTION()
	void ResetMaterial();
	UFUNCTION()
	void SetTrapCooldown(AActor* OtherActor);
	UFUNCTION()
	void ResetTrapCooldown(AActor* OtherActor);
	
	UPROPERTY(EditAnywhere, Category="Traps Settings|Damage")
	float CooldownDuration = 5.f;
	UPROPERTY(VisibleAnywhere, Category="Traps Settings|Damage")
	bool bIsTrapCooldown;
	
	FTimerHandle DamageTimerHandle;
	FTimerHandle RedColorTimerHandle;
	FTimerHandle DamageCooldownHandle;
	FTimerHandle CooldownHandle;
	
	UFUNCTION()
	void DamagePrepare(AActor* OtherActor);
	UFUNCTION()
	void Damage(AActor* OtherActor);
	
	UPROPERTY(EditAnywhere, Category="Traps Settings|Damage")
	float TimeForDamage = 1.f;
	UPROPERTY(EditAnywhere, Category="Traps Settings|Damage")
	float MaterialResetTime = 0.3f;
	
	UPROPERTY(EditAnywhere, Category="Traps Settings|Damage") 
	float TrapDamage = 30.f;
	UPROPERTY(EditAnywhere, Category="Traps Settings|Damage")
	FLinearColor BaseColor = FLinearColor::Gray;
	UPROPERTY(EditAnywhere, Category="Traps Settings|Damage")
	FLinearColor ActiveColor = FLinearColor(1.0f, 0.5f, 0.0f);
	UPROPERTY(EditAnywhere, Category="Traps Settings|Damage")
	FLinearColor DamageColor = FLinearColor::Red;
	virtual  void ResetTimer()  override;


protected:
	virtual void BeginPlay() override;
	
		
};
