// Fill out your copyright notice in the Description page of Project Settings.


#include "TrapDamage.h"
#include "Kismet/GameplayStatics.h"
#include "TimerManager.h"
// Sets default values
ATrapDamage::ATrapDamage()
{

    DamageRate = 1.0f; // »нтервал между ударами в секундах
    DamageAmount = 10.0f; //  оличество урона при каждом ударе
    DamageColdawn = 5.0f;

    bCanInflictDamage = true;

    UStaticMesh* SM_Vase = Cast<UStaticMesh>(StaticLoadObject(UStaticMesh::StaticClass(), NULL, TEXT("/Game/LevelPrototyping/Meshes/Title")));

    StaticMeshComponent = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("StaticMeshComponent"));
    StaticMeshComponent->SetStaticMesh(SM_Vase);

    NormalMaterial = LoadObject<UMaterialInterface>(nullptr, TEXT("/Game/LevelPrototyping/Materials/TrapDamage/TrapDamage_Normal"));; 
    ActivatedMaterial = LoadObject<UMaterialInterface>(nullptr, TEXT("/Game/LevelPrototyping/Materials/TrapDamage/TrapDamage_Activation"));
    DamageMaterial = LoadObject<UMaterialInterface>(nullptr, TEXT("/Game/LevelPrototyping/Materials/TrapDamage/TrapDamage_Damage"));

    StaticMeshComponent->SetMaterial(0, NormalMaterial);
    StaticMeshComponent->SetCollisionResponseToAllChannels(ECollisionResponse::ECR_Overlap);
    OnActorBeginOverlap.AddDynamic(this, &ATrapDamage::OnOverlap);
    OnActorEndOverlap.AddDynamic(this, &ATrapDamage::OnOverlapEnd);
}

// Called when the game starts or when spawned
void ATrapDamage::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ATrapDamage::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}
void ATrapDamage::OnOverlap(AActor* MyOverlappedActor, AActor* OtherActor)
{
    if (OtherActor && OtherActor != this)
    {
        MyCharacter = Cast<APlatfomerCharacter>(OtherActor);
        if (MyCharacter)
        {
            // ≈сли персонаж находитс€ на ловушке, установите таймер дл€ нанесени€ урона
            bCanInflictDamage = true;
            StaticMeshComponent->SetMaterial(0, ActivatedMaterial);
            GetWorldTimerManager().SetTimer(TimerHandle_Damage, this, &ATrapDamage::InflictDamage, DamageRate, true);
        }
    }
}


void ATrapDamage::InflictDamage()
{
 
        MyCharacter = Cast<APlatfomerCharacter>(GetWorld()->GetFirstPlayerController()->GetPawn());
        if (MyCharacter && bCanInflictDamage)
        {
            StaticMeshComponent->SetMaterial(0, DamageMaterial);
            MyCharacter->UpdateHealth(-DamageAmount);
            GetWorldTimerManager().SetTimer(TimerHandle_Reset, this, &ATrapDamage::ResetTrap, DamageColdawn, true);
            bCanInflictDamage = false;
        }
    
}

void ATrapDamage::OnOverlapEnd(AActor* MyOverlappedActor, AActor* OtherActor)
{
    if (OtherActor && OtherActor != this)
    {
        MyCharacter = Cast<APlatfomerCharacter>(OtherActor);
        if (MyCharacter)
        {
            bCanInflictDamage = false;
            GetWorldTimerManager().ClearTimer(TimerHandle_Reset);
            StaticMeshComponent->SetMaterial(0, NormalMaterial);
        }
    }
}
void ATrapDamage::ResetTrap() {
    StaticMeshComponent->SetMaterial(0, ActivatedMaterial);
    bCanInflictDamage = true;
}