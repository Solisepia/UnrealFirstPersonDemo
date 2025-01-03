// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "MyFirstPGameMode.generated.h"

UCLASS(minimalapi)
class AMyFirstPGameMode : public AGameModeBase
{
	GENERATED_BODY()

public:
	AMyFirstPGameMode();

	UFUNCTION(BlueprintImplementableEvent, Category = "GameMode")
	void OnEndGameBlueprint();

	UFUNCTION(BlueprintCallable, Category = "GameMode")
	void RestartGame();

protected:
	virtual void BeginPlay();

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = Game, meta = (AllowPrivateAccess = "true"))
	int CountDownTime;
	
	FTimerHandle CountDownTimer;

	void CountDownTimerTick();
	
	void EndGame();

	void PauseGame();
	
};



