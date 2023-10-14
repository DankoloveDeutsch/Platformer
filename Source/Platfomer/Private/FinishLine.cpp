// Fill out your copyright notice in the Description page of Project Settings.


#include "FinishLine.h"
#include "Kismet/GameplayStatics.h"
// Sets default values
AFinishLine::AFinishLine()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	//PrimaryActorTick.bCanEverTick = true;
	UStaticMesh* SM_Vase = Cast<UStaticMesh>(StaticLoadObject(UStaticMesh::StaticClass(), NULL, TEXT("/Game/LevelPrototyping/Meshes/StartFinishLin")));

	StaticMeshComponent = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("StaticMeshComponent"));
	StaticMeshComponent->SetStaticMesh(SM_Vase);
	StaticMeshComponent->SetCollisionResponseToAllChannels(ECollisionResponse::ECR_Overlap);

	StaticMeshComponent->OnComponentEndOverlap.AddDynamic(this, &AFinishLine::OnFinishLineEndOverlap);
}

// Called when the game starts or when spawned
void AFinishLine::BeginPlay()
{
	Super::BeginPlay();
	MyGameMode = Cast<APlatfomerGameMode>(UGameplayStatics::GetGameMode(GetWorld()));
}

// Called every frame
void AFinishLine::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}
void AFinishLine::OnFinishLineEndOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex) {
	MyGameMode->SetCurrentState(EGamePlayState::EWin);
}
