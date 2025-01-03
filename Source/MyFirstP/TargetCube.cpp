// Fill out your copyright notice in the Description page of Project Settings.


#include "TargetCube.h"

#include "MyFirstPProjectile.h"
#include "Engine.h"

// Sets default values
ATargetCube::ATargetCube()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	
	BIsHitOnce = false;
}

// Called when the game starts or when spawned
void ATargetCube::BeginPlay()
{
	Super::BeginPlay();
}

// Called every frame
void ATargetCube::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void ATargetCube::OnHit(UPrimitiveComponent* HitComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit)
{
	if (OtherActor && OtherActor->IsA(AMyFirstPProjectile::StaticClass()))
	{
		if (!BIsHitOnce)
		{
			BIsHitOnce = true;
			FVector NewScale = GetActorScale3D() * 0.5f;
			SetActorScale3D(NewScale);
		}
		else
		{
			Destroy();
		}
	}
}
