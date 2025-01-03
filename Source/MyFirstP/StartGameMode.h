// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "Blueprint/UserWidget.h"


#include "StartGameMode.generated.h"

/**
 * 
 */
UCLASS()
class MYFIRSTP_API AStartGameMode : public AGameModeBase
{
	GENERATED_BODY()

public:
	AStartGameMode();

	UFUNCTION(BlueprintCallable, Category = "StartGameMode")
	void SyncLoadMap(FString MapName);

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "StartGameMode")
	float LoadPercent;

protected:
	virtual void BeginPlay() override;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "UI")
	TSubclassOf<UUserWidget> WidgetBlueprintClass;

	void OnMapLoaded(const FName& PackageName, UPackage* LoadedPackage, EAsyncLoadingResult::Type Result);

	void UpdateProgress();

	FTimerHandle ProgressTimerHandle;

	FName MapPackageName;
};
