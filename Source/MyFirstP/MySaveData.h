// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/SaveGame.h"
#include "MySaveData.generated.h"

/**
 * 
 */
UCLASS()
class MYFIRSTP_API UMySaveData : public USaveGame
{
	GENERATED_BODY()

public:
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category=GameData)
	FString Username;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category=GameData)
	FString Password;

	UMySaveData();
};
