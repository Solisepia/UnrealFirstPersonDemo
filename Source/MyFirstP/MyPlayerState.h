// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerState.h"
#include "MyPlayerState.generated.h"

/**
 * 
 */
UCLASS()
class MYFIRSTP_API AMyPlayerState : public APlayerState
{
	GENERATED_BODY()

public:
	AMyPlayerState();
	
	UPROPERTY(BlueprintReadOnly, Category = Player, meta = (AllowPrivateAccess = "true"))
	int CurrentHealth;

	UPROPERTY(BlueprintReadOnly, Category = Player, meta = (AllowPrivateAccess = "true"))
	int MaxHealth;
};
