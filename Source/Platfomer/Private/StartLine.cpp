// Fill out your copyright notice in the Description page of Project Settings.


#include "StartLine.h"
#include "Kismet/GameplayStatics.h"
// Sets default values
AStartLine::AStartLine()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	//PrimaryActorTick.bCanEverTick = true;


	UStaticMesh* SM_Vase = Cast<UStaticMesh>(StaticLoadObject(UStaticMesh::StaticClass(), NULL, TEXT("/Game/LevelPrototyping/Meshes/StartFinishLin")));

	StaticMeshComponent = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("StaticMeshComponent"));
	StaticMeshComponent->SetStaticMesh(SM_Vase);
	StaticMeshComponent->SetCollisionResponseToAllChannels(ECollisionResponse::ECR_Overlap);
	StaticMeshComponent->OnComponentEndOverlap.AddDynamic(this, &AStartLine::OnStartLineEndOverlap);
}

// Called when the game starts or when spawned
void AStartLine::BeginPlay()
{
	Super::BeginPlay();
	MyGameMode = Cast<APlatfomerGameMode>(UGameplayStatics::GetGameMode(GetWorld()));
}

// Called every frame
void AStartLine::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void AStartLine::OnStartLineEndOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex) {
	MyGameMode->StartTimer();
}

