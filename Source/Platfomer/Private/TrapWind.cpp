// Fill out your copyright notice in the Description page of Project Settings.


#include "TrapWind.h"
#include "../PlatfomerCharacter.h" 
#include "Kismet/GameplayStatics.h"
#include "GameFramework/CharacterMovementComponent.h"
// Sets default values
ATrapWind::ATrapWind()
{
    PrimaryActorTick.bCanEverTick = true;
    NormalMaterial = LoadObject<UMaterialInterface>(nullptr, TEXT("/Game/LevelPrototyping/Materials/Wind"));
    ActivatedMaterial = LoadObject<UMaterialInterface>(nullptr, TEXT("/Game/LevelPrototyping/Materials/M_Solid"));
    WindChange = false;

    WindForce = 200.0f; 
    WindDirection = FVector(1.0f, 0.0f, 0.0f);
    ChangeCooldown = 2.0f;

    UStaticMesh* TrapWind = Cast<UStaticMesh>(StaticLoadObject(UStaticMesh::StaticClass(), NULL, TEXT("/Game/LevelPrototyping/Meshes/plate")));

    StaticMeshComponent = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("StaticMeshComponent"));
    StaticMeshComponent->SetStaticMesh(TrapWind);
    StaticMeshComponent->SetMaterial(0, NormalMaterial);
    StaticMeshComponent->SetCollisionResponseToAllChannels(ECollisionResponse::ECR_Overlap);

    StaticMeshComponent->OnComponentBeginOverlap.AddDynamic(this, &ATrapWind::OnTrapOverlap);
    StaticMeshComponent->OnComponentEndOverlap.AddDynamic(this, &ATrapWind::OnTrapEndOverlap);

}

// Called when the game starts or when spawned
void ATrapWind::BeginPlay()
{
	Super::BeginPlay();

    GetWorldTimerManager().SetTimer(TimerHandle_Change, this, &ATrapWind::ChangeDirection, ChangeCooldown, true);
}

// Called every frame
void ATrapWind::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
    ATrapWind::WindAction(DeltaTime);
    UE_LOG(LogTemp, Warning, TEXT("Im working TICK"));
}

// ������� ����� ����������� �����
void ATrapWind::ChangeDirection() {

    float RandomX = FMath::FRandRange(-1.0f, 1.0f);
    float RandomY = FMath::FRandRange(-1.0f, 1.0f);
    WindDirection = FVector(RandomX, RandomY, 0.0f).GetSafeNormal();
}
// ������� �������� �����
void ATrapWind::WindAction(float DeltaTime) {
    UE_LOG(LogTemp, Warning, TEXT("Im working"));
    if (WindChange)
    {
        
        MyCharacter = Cast<APlatfomerCharacter>(UGameplayStatics::GetPlayerCharacter(this, 0));
        if (MyCharacter)
        {

            FVector WindForceVector = MyCharacter->GetActorLocation();

            WindForceVector += WindDirection * WindForce * DeltaTime;

            MyCharacter->SetActorLocation(WindForceVector);
            
        }
    }
    

}
// ��������� �����
void ATrapWind::EnableWind()
{
    WindChange = true;
    StaticMeshComponent->SetMaterial(0, ActivatedMaterial);
}
// ������������ �����
void ATrapWind::DisableWind()
{
    WindChange = false;
    StaticMeshComponent->SetMaterial(0, NormalMaterial);
}
// ������ �������������� � ����������
void ATrapWind::OnTrapOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult) {
    MyCharacter = Cast<APlatfomerCharacter>(OtherActor);
    if (MyCharacter)
    {
        EnableWind();
    }
}
// ����� �������������� � ����������
void ATrapWind::OnTrapEndOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex) {
    
    MyCharacter = Cast<APlatfomerCharacter>(OtherActor);
    if (MyCharacter)
    {
        DisableWind();
    }
}