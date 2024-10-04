// Fill out your copyright notice in the Description page of Project Settings.


#include "TrapRotateZ.h"

// Sets default values
ATrapRotateZ::ATrapRotateZ()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
    TrapMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("TrapMesh"));

    
    // ��������� ������ � �������� ��� �������
    static ConstructorHelpers::FObjectFinder<UStaticMesh> TrapMeshAsset(TEXT("/Game/LevelPrototyping/Meshes/plate"));
    if (TrapMeshAsset.Succeeded())
    {
        TrapMesh->SetStaticMesh(TrapMeshAsset.Object);
    }
    NormalMaterial = LoadObject<UMaterialInterface>(nullptr, TEXT("/Game/LevelPrototyping/Materials/TrapDamage/TrapDamage_Normal"));
    TrapMesh->SetMaterial(0, NormalMaterial);
    RotationSpeed = 20.0f;
}

// Called when the game starts or when spawned
void ATrapRotateZ::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ATrapRotateZ::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
    RotateTrap(DeltaTime);
}
void ATrapRotateZ::RotateTrap(float DeltaTime)
{
    // �������� �������, ������� � ���� ��������
    FRotator NewRotation = GetActorRotation();
    NewRotation.Roll += RotationSpeed * DeltaTime; // RotationSpeed - �������� ��������
    SetActorRotation(NewRotation);
}

