#pragma once

#include "CoreMinimal.h"
#include "TrapBaseComponent.h"
#include "TrapBase.h"
#include "Components/BoxComponent.h"
#include "TrapWindComponent.generated.h"

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class PLATFOMER_API UTrapWindComponent : public UTrapBaseComponent
{
	GENERATED_BODY()

public:

	UTrapWindComponent();
	
	FTimerHandle WindTimerHandle;
	FTimerHandle WindChangeHandle;
	
	UFUNCTION()
	void Wind(AActor* OtherActor);
	UFUNCTION()
	void WindApply(AActor* OtherActor);
	UFUNCTION()
	void WindChange(AActor* OtherActor,FVector WindDirection);


	UPROPERTY(EditAnywhere, Category="Traps Settings|Wind")
	float WindChangeRate = 2.f;
	
	UPROPERTY(EditAnywhere, Category="Traps Settings|Wind")
	float WindPressure = 1.f;
\
	
	UPROPERTY(EditAnywhere, Category="Traps Settings|Wind")
	float MaxWindPower = 100.f;

	UPROPERTY(EditAnywhere, Category="Traps Settings|Wind")
	float MinWindPower = 30.f;
	UPROPERTY()
	float WindPower = 0.f;

	UPROPERTY(EditAnywhere, Category="Traps Settings|Wind")
	FLinearColor BaseColor = FLinearColor::Gray;
	UPROPERTY(EditAnywhere, Category="Traps Settings|Wind")
	FLinearColor ActiveColor = FLinearColor::Blue;

	UPROPERTY()
	float RandomX;

	UPROPERTY()
    float RandomY;
	
	virtual void ResetTimer() override;
	
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;
	
	virtual void OnOverlapBegin(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult) override;
	virtual void OnOverlapEnd(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex) override;
	 

protected:
	virtual void BeginPlay() override;
	
};
