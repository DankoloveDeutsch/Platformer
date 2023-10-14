// Fill out your copyright notice in the Description page of Project Settings.


#include "TrapWind.h"
#include "../PlatfomerCharacter.h" 
#include "Kismet/GameplayStatics.h"
#include "GameFramework/CharacterMovementComponent.h"
// Sets default values
ATrapWind::ATrapWind()
{
    PrimaryActorTick.bCanEverTick = true;
    NormalMaterial = LoadObject<UMaterialInterface>(nullptr, TEXT("/Game/LevelPrototyping/Materials/TrapDamage/TrapDamage_Normal"));
    ActivatedMaterial = LoadObject<UMaterialInterface>(nullptr, TEXT("/Game/LevelPrototyping/Materials/TrapDamage/TrapDamage_Activation"));
    WindChange = false;

    WindForce = 200.0f; 
    WindDirection = FVector(1.0f, 0.0f, 0.0f);
    ChangeCooldown = 2.0f;

    UStaticMesh* SM_Vase = Cast<UStaticMesh>(StaticLoadObject(UStaticMesh::StaticClass(), NULL, TEXT("/Game/LevelPrototyping/Meshes/Title")));

    StaticMeshComponent = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("StaticMeshComponent"));
    StaticMeshComponent->SetStaticMesh(SM_Vase);
    StaticMeshComponent->SetMaterial(0, NormalMaterial);
    StaticMeshComponent->SetCollisionResponseToAllChannels(ECollisionResponse::ECR_Overlap);

    StaticMeshComponent->OnComponentBeginOverlap.AddDynamic(this, &ATrapWind::OnTrapOverlap);
    StaticMeshComponent->OnComponentEndOverlap.AddDynamic(this, &ATrapWind::OnTrapEndOverlap);

    

   // OnActorBeginOverlap.AddDynamic(this, &ATrapWind::OnOverlap);
    //OnActorEndOverlap.AddDynamic(this, &ATrapWind::OnOverlapEnd);

}

// Called when the game starts or when spawned
void ATrapWind::BeginPlay()
{
	Super::BeginPlay();
    //GetWorld()->GetTimerManager().SetTimer(WindChangeTimer, this, &ATrapWind::ChangeDirection, ChangeCooldown, true);
    GetWorldTimerManager().SetTimer(TimerHandle_Change, this, &ATrapWind::ChangeDirection, ChangeCooldown, true);
}

// Called every frame
void ATrapWind::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
    ATrapWind::WindAction(DeltaTime);
    UE_LOG(LogTemp, Warning, TEXT("Im working TICK"));
}

// Функция смены направления ветра
void ATrapWind::ChangeDirection() {

    float RandomX = FMath::FRandRange(-1.0f, 1.0f);
    float RandomY = FMath::FRandRange(-1.0f, 1.0f);
    WindDirection = FVector(RandomX, RandomY, 0.0f).GetSafeNormal();
}
// Функция действия ветра
void ATrapWind::WindAction(float DeltaTime) {
    UE_LOG(LogTemp, Warning, TEXT("Im working"));
    if (WindChange)
    {
        
        MyCharacter = Cast<APlatfomerCharacter>(UGameplayStatics::GetPlayerCharacter(this, 0));
        if (MyCharacter)
        {

            FVector WindForceVector = MyCharacter->GetActorLocation();

            // Добавляем ветровую силу к персонажу
            WindForceVector += WindDirection * WindForce * DeltaTime;

            MyCharacter->SetActorLocation(WindForceVector);
            
            

            //MyCharacter->LaunchCharacter(WindDirection * WindForce, false, false);
        }
    }
    

}
// Активация ветра
void ATrapWind::EnableWind()
{
    WindChange = true;
    StaticMeshComponent->SetMaterial(0, ActivatedMaterial);
}
// Дезактивация ветра
void ATrapWind::DisableWind()
{
    WindChange = false;
    StaticMeshComponent->SetMaterial(0, NormalMaterial);
}
// Начало взаимодействия с персонажем
void ATrapWind::OnTrapOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult) {
    MyCharacter = Cast<APlatfomerCharacter>(OtherActor);
    if (MyCharacter)
    {
        EnableWind();
    }
}
// Конец взаимодействия с персонажем
void ATrapWind::OnTrapEndOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex) {
    
    MyCharacter = Cast<APlatfomerCharacter>(OtherActor);
    if (MyCharacter)
    {
        DisableWind();
    }
}