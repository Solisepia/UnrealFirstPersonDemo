// Copyright Epic Games, Inc. All Rights Reserved.
#include "MyFirstPProjectile.h"

#include "MyPlayerState.h"
#include "GameFramework/ProjectileMovementComponent.h"
#include "Components/SphereComponent.h"
#include "TargetCube.h"
#include "MyFirstPCharacter.h"


AMyFirstPProjectile::AMyFirstPProjectile()
	: Shooter(nullptr)
{
	// Use a sphere as a simple collision representation
	CollisionComp = CreateDefaultSubobject<USphereComponent>(TEXT("SphereComp"));
	CollisionComp->InitSphereRadius(5.0f);
	CollisionComp->BodyInstance.SetCollisionProfileName("Projectile");
	CollisionComp->OnComponentHit.AddDynamic(this, &AMyFirstPProjectile::OnHit);		// set up a notification for when this component hits something blocking

	// Players can't walk on it
	CollisionComp->SetWalkableSlopeOverride(FWalkableSlopeOverride(WalkableSlope_Unwalkable, 0.f));
	CollisionComp->CanCharacterStepUpOn = ECB_No;

	// Set as root component
	RootComponent = CollisionComp;

	// Use a ProjectileMovementComponent to govern this projectile's movement
	ProjectileMovement = CreateDefaultSubobject<UProjectileMovementComponent>(TEXT("ProjectileComp"));
	ProjectileMovement->UpdatedComponent = CollisionComp;
	ProjectileMovement->InitialSpeed = 3000.f;
	ProjectileMovement->MaxSpeed = 3000.f;
	ProjectileMovement->bRotationFollowsVelocity = true;
	ProjectileMovement->bShouldBounce = true;

	// Die after 3 seconds by default
	InitialLifeSpan = 3.0f;
}

void AMyFirstPProjectile::OnHit(UPrimitiveComponent* HitComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit)
{
	// Only add impulse and destroy projectile if we hit a physics
	if ((OtherActor != nullptr) && (OtherActor != this) && (OtherComp != nullptr) && OtherComp->IsSimulatingPhysics())
	{
		OtherComp->AddImpulseAtLocation(GetVelocity() * 100.0f, GetActorLocation());
		if (OtherActor->IsA(ATargetCube::StaticClass()))
		{
			if (Shooter)
			{
				AMyPlayerState* PlayerState = Cast<AMyPlayerState>(Shooter->PlayerState);
				PlayerState->SetScore(PlayerState->GetScore()+1);
			}
		}
		Destroy();
	}
	else if (OtherActor->IsA(ACharacter::StaticClass()))
	{
		if (AMyFirstPCharacter* Character = Cast<AMyFirstPCharacter>(OtherActor))
		{
			Destroy();
		}
		else
		{
			if (Shooter)
			{
				AMyPlayerState* PlayerState = Cast<AMyPlayerState>(Shooter->PlayerState);
				PlayerState->SetScore(PlayerState->GetScore()+2);
			}
		}
	}
}