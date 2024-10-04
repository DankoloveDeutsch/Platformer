// Fill out your copyright notice in the Description page of Project Settings.


#include "TrapDamage.h"

// Sets default values
ATrapDamage::ATrapDamage()
{

    DamageRate = 1.0f; 
    DamageAmount = 10.0f; 
    DamageColdawn = 5.0f;

    bCanInflictDamage = true;

    StaticMeshComponent = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("StaticMeshComponent"));
    RootComponent = StaticMeshComponent;

    static ConstructorHelpers::FObjectFinder<UStaticMesh> SM_Asset(TEXT("/Game/LevelPrototyping/Meshes/plate"));
    if (SM_Asset.Succeeded())
    {
        StaticMeshComponent->SetStaticMesh(SM_Asset.Object);
    }

    static ConstructorHelpers::FObjectFinder<UMaterialInterface> NormalMatAsset(TEXT("/Game/LevelPrototyping/Materials/TrapDamage/TrapDamage_Normal"));
    if (NormalMatAsset.Succeeded())
    {
        NormalMaterial = NormalMatAsset.Object;
    }
    static ConstructorHelpers::FObjectFinder<UMaterialInterface> ActivatedMatAsset(TEXT("/Game/LevelPrototyping/Materials/TrapDamage/TrapDamage_Activation"));
    if (ActivatedMatAsset.Succeeded())
    {
        ActivatedMaterial = ActivatedMatAsset.Object;
    }
    static ConstructorHelpers::FObjectFinder<UMaterialInterface> DamageMatAsset(TEXT("/Game/LevelPrototyping/Materials/TrapDamage/TrapDamage_Damage"));
    if (DamageMatAsset.Succeeded())
    {
        DamageMaterial = DamageMatAsset.Object;
    }

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
        if (MyCharacter and !GetWorldTimerManager().IsTimerActive(TimerHandle_Damage))
        {
            //OverlappingCharacter = Cast<APlatfomerCharacter>(MyCharacter->GetWorld()->GetFirstPlayerController()->GetPawn());
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