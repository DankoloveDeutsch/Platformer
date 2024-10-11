#include "TrapBase.h"
#include "TrapDamageComponent.h"
#include "Components/BoxComponent.h"
#include "Components/StaticMeshComponent.h"

ATrapBase::ATrapBase()
{
	PrimaryActorTick.bCanEverTick = true;

	Platform = CreateDefaultSubobject<UStaticMeshComponent>("Platform");
	RootComponent = Platform;
	static ConstructorHelpers::FObjectFinder<UStaticMesh>MeshAsset(TEXT("/Game/LevelPrototyping/Meshes/plate"));
	if (MeshAsset.Succeeded())
	{
		Platform->SetStaticMesh(MeshAsset.Object);

	}
	
	CollisionComp = CreateDefaultSubobject<UBoxComponent>("Interact Collision");
	CollisionComp->SetupAttachment(Platform);
	CollisionComp->SetRelativeLocation(FVector(0.0f,0.0f,5.0f));
	CollisionComp->SetBoxExtent(FVector(300.0f,300.0f,10.0f));
}

void ATrapBase::BeginPlay()
{
	Super::BeginPlay();
	DynamicMaterial = UMaterialInstanceDynamic::Create(Platform->GetMaterial(0),this);
	Platform->SetMaterial(0,DynamicMaterial);
	DynamicMaterial->SetVectorParameterValue(TEXT("Color"), FLinearColor::White);
}

void ATrapBase::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void ATrapBase::ChangeMaterialColor(FLinearColor color)
{
	DynamicMaterial->SetVectorParameterValue(TEXT("Color"), color);
}

void ATrapBase::ResetTimers()
{
	TArray<UTrapBaseComponent*> Components;
	GetComponents<UTrapBaseComponent>(Components);
	for (UTrapBaseComponent* Comp : Components)
	{
		Comp->ResetTimer();
	}
}
