// Fill out your copyright notice in the Description page of Project Settings.


#include "TrapIce.h"

// Sets default values
ATrapIce::ATrapIce()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	UStaticMesh* SM_Vase = Cast<UStaticMesh>(StaticLoadObject(UStaticMesh::StaticClass(), NULL, TEXT("/Game/LevelPrototyping/Meshes/plate")));

    StaticMeshComponent = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("StaticMeshComponent"));
    StaticMeshComponent->SetStaticMesh(SM_Vase);
    NormalMaterial = LoadObject<UMaterialInterface>(nullptr, TEXT("/Game/LevelPrototyping/Materials/TrapDamage/TrapDamage_Normal"));
    
    StaticMeshComponent->SetMaterial(0, NormalMaterial);
    StaticMeshComponent->SetCollisionResponseToAllChannels(ECollisionResponse::ECR_Overlap);
    OnActorBeginOverlap.AddDynamic(this, &ATrapIce::OnOverlap);
    OnActorEndOverlap.AddDynamic(this, &ATrapIce::OnOverlapEnd);
    
}

// Called when the game starts or when spawned
void ATrapIce::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ATrapIce::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void ATrapIce::OnOverlap(AActor* MyOverlappedActor, AActor* OtherActor){
	MyCharacter = Cast<APlatfomerCharacter>(OtherActor);
    if (MyCharacter)
    {
		MyCharacter->GetCharacterMovement()->GroundFriction = 0.0f;
		MyCharacter->GetCharacterMovement()->BrakingDecelerationWalking = 350.0f;
    }
}

void ATrapIce::OnOverlapEnd(AActor* MyOverlappedActor, AActor* OtherActor){
	if (OtherActor && OtherActor != this)
    {
        MyCharacter = Cast<APlatfomerCharacter>(OtherActor);
        if (MyCharacter)
        {
            MyCharacter->GetCharacterMovement()->GroundFriction = 8.0f;
			MyCharacter->GetCharacterMovement()->BrakingDecelerationWalking = 2000.0f;
            MyCharacter = nullptr; 
        }
    }
}
ATrapIce::~ATrapIce()
{

}