// Fill out your copyright notice in the Description page of Project Settings.


#include "Bullet.h"
#include "Engine/DecalActor.h"
#include "Components/DecalComponent.h"

// Sets default values
ABullet::ABullet()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	SceneComponent = CreateDefaultSubobject<USceneComponent>(TEXT("SceneComponent"));
	RootComponent = SceneComponent;

	MeshComponent = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Mesh"));
	MeshComponent->SetRelativeLocation(SceneComponent->GetComponentLocation());
	MeshComponent->SetupAttachment(RootComponent);

	MovementComponent = CreateDefaultSubobject<UProjectileMovementComponent >(TEXT("MovementComponent"));
	MovementComponent->InitialSpeed = 2000;
	MovementComponent->MaxSpeed = 2000;
}

// Called when the game starts or when spawned
void ABullet::BeginPlay()
{
	Super::BeginPlay();

	MeshComponent->OnComponentBeginOverlap.AddDynamic(this, &ABullet::OnOverlapBegin);
}

// Called every frame
void ABullet::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void ABullet::OnOverlapBegin(UPrimitiveComponent* HitComp, AActor* OtherActor, UPrimitiveComponent* OtherComp,
	int32 OtherIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	FRotator rotationDecall = GetActorRotation() - FRotator(-90, 0, 0);
	rotationDecall.Normalize();

	ADecalActor* decal = GetWorld()->SpawnActor<ADecalActor>(GetActorLocation(), rotationDecall);
	decal->SetDecalMaterial(decalKirby);
	decal->GetDecal()->DecalSize = FVector(100, 100, 100);
	decal->GetDecal()->SetFadeOut(1, 3, true);

	Destroy();
}

