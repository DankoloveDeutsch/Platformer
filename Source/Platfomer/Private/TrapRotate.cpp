// Fill out your copyright notice in the Description page of Project Settings.


#include "TrapRotate.h"

// Sets default values
ATrapRotate::ATrapRotate()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
    TrapMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("TrapMesh"));

    
    // Загрузите модель и материал для ловушки
    static ConstructorHelpers::FObjectFinder<UStaticMesh> TrapMeshAsset(TEXT("/Game/LevelPrototyping/Meshes/Title"));
    if (TrapMeshAsset.Succeeded())
    {
        TrapMesh->SetStaticMesh(TrapMeshAsset.Object);
    }
    NormalMaterial = LoadObject<UMaterialInterface>(nullptr, TEXT("/Game/LevelPrototyping/Materials/TrapDamage/TrapDamage_Normal"));
    TrapMesh->SetMaterial(0, NormalMaterial);
    RotationSpeed = 20.0f;
}

// Called when the game starts or when spawned
void ATrapRotate::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ATrapRotate::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
    RotateTrap(DeltaTime);
}
void ATrapRotate::RotateTrap(float DeltaTime)
{
    // Вращайте ловушку, изменяя её угол поворота
    FRotator NewRotation = GetActorRotation();
    NewRotation.Yaw += RotationSpeed * DeltaTime; // RotationSpeed - скорость вращения
    SetActorRotation(NewRotation);
}
