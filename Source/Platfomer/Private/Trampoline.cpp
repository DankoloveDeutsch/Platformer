// Fill out your copyright notice in the Description page of Project Settings.


#include "Trampoline.h"

// Sets default values
ATrampoline::ATrampoline()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	UStaticMesh* SM_Vase = Cast<UStaticMesh>(StaticLoadObject(UStaticMesh::StaticClass(), NULL, TEXT("/Game/LevelPrototyping/Meshes/plate")));

    StaticMeshComponent = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("StaticMeshComponent"));
    StaticMeshComponent->SetStaticMesh(SM_Vase);
    NormalMaterial = LoadObject<UMaterialInterface>(nullptr, TEXT("/Game/LevelPrototyping/Materials/TrapDamage/TrapDamage_Normal"));
    
    StaticMeshComponent->SetMaterial(0, NormalMaterial);
    StaticMeshComponent->SetCollisionResponseToAllChannels(ECollisionResponse::ECR_Overlap);
    OnActorBeginOverlap.AddDynamic(this, &ATrampoline::OnOverlap);

	ForceBoost = 1000.0f;
}

// Called when the game starts or when spawned
void ATrampoline::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ATrampoline::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}
void ATrampoline::OnOverlap(AActor* MyOverlappedActor, AActor* OtherActor) {
    MyCharacter = Cast<APlatfomerCharacter>(OtherActor);
    if (MyCharacter) {
        MyCharacter->LaunchCharacter(FVector(0.0f, 0.0f, ForceBoost), false, false);
    }
}