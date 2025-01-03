// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "TargetCube.generated.h"

UCLASS()
class MYFIRSTP_API ATargetCube : public AActor
{
	GENERATED_BODY()

	bool BIsHitOnce;

	
	
public:	
	// Sets default values for this actor's properties
	ATargetCube();

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	class UStaticMeshComponent* CubeMesh;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	UFUNCTION(BlueprintCallable, Category = Cube)
	void OnHit(UPrimitiveComponent* HitComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit);
};
