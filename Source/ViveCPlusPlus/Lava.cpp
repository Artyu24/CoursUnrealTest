// Fill out your copyright notice in the Description page of Project Settings.


#include "Lava.h"

#include "ViveCPlusPlusCharacter.h"

// Sets default values
ALava::ALava()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	MeshComponent = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Mesh"));
	RootComponent = MeshComponent;
}

// Called when the game starts or when spawned
void ALava::BeginPlay()
{
	Super::BeginPlay();

	MeshComponent->OnComponentHit.AddDynamic(this, &ALava::OnHit);
}

// Called every frame
void ALava::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void ALava::OnHit(UPrimitiveComponent* HitComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit)
{
	AViveCPlusPlusCharacter* Character = Cast<AViveCPlusPlusCharacter>(OtherActor);
	if (Character == nullptr)
		return;

	Character->Ragdoll();
}

