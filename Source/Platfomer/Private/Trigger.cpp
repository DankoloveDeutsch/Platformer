// Fill out your copyright notice in the Description page of Project Settings.


#include "Trigger.h"


ATrigger::ATrigger()
{
}
void ATrigger::BeginPlay()
{
    Super::BeginPlay();
    OnActorBeginOverlap.AddDynamic(this, &ATrigger::OnOverlapBegin);
}

void ATrigger::OnOverlapBegin(class AActor* OverlappedActor, class AActor* OtherActor)
{
    APlayerController* Controller = UGameplayStatics::GetPlayerController(GetWorld(), 0);
    APlatfomerCharacter* Player = Cast<APlatfomerCharacter>(Controller->GetPawn());

    if (Player && Player == OtherActor){
    
        if (this->ActorHasTag("Win")){
            OnGameOver.Broadcast(true);
            return;
        }

        if (this->ActorHasTag("Lose"))
        {
            OnGameOver.Broadcast(false);
            return;
        }
        
        if (this->ActorHasTag("Start"))
        {
            
            if (!bTriggerActivated)
            {
                TrapsStart.Broadcast();
                OnStart.Broadcast(UGameplayStatics::GetRealTimeSeconds(GetWorld()));
                bTriggerActivated = true;
            }
            return;
        }
    }
}