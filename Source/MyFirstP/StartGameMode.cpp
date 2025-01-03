// Fill out your copyright notice in the Description page of Project Settings.


#include "StartGameMode.h"


#include "Kismet/GameplayStatics.h"

AStartGameMode::AStartGameMode()
	: Super(), LoadPercent()
{
	static ConstructorHelpers::FClassFinder<UUserWidget> WidgetStartUIClass(TEXT("/Script/UMGEditor.WidgetBlueprint'/Game/FirstPerson/UIBlueprints/StartUI_WidgetBP.StartUI_WidgetBP_C'"));
	if (WidgetStartUIClass.Succeeded())
	{
		WidgetBlueprintClass = WidgetStartUIClass.Class;
	}
	else
	{
		UE_LOG(LogTemp, Warning, TEXT("Failed to find Widget Blueprint class."));
	}
}

void AStartGameMode::BeginPlay()
{
	Super::BeginPlay();
	
	APlayerController* PlayerController = GetWorld()->GetFirstPlayerController();
	if (PlayerController)
	{
		PlayerController->SetInputMode(FInputModeUIOnly());
		if (UUserWidget* MyWidget = CreateWidget<UUserWidget>(PlayerController, WidgetBlueprintClass))
			MyWidget->AddToViewport();
	}
}

void AStartGameMode::SyncLoadMap(FString MapName)
{
	FString PackagePath = FString::Printf(TEXT("/Game/FirstPerson/Maps/%s"), *MapName);
	MapPackageName = FName(*PackagePath);
	LoadPackageAsync(PackagePath, FLoadPackageAsyncDelegate::CreateUObject(this, &AStartGameMode::OnMapLoaded));
	GetWorld()->GetTimerManager().SetTimer(ProgressTimerHandle, this, &AStartGameMode::UpdateProgress, 0.01f, true);
}

void AStartGameMode::OnMapLoaded(const FName& PackageName, UPackage* LoadedPackage, EAsyncLoadingResult::Type Result)
{
	//GetWorld()->GetTimerManager().ClearTimer(ProgressTimerHandle);

	if (Result == EAsyncLoadingResult::Type::Succeeded)
	{
		UGameplayStatics::OpenLevel(this, MapPackageName);
	}
	else
		UE_LOG(LogTemp, Warning, TEXT("Failed to load map."));
}

void AStartGameMode::UpdateProgress()
{
	LoadPercent = GetAsyncLoadPercentage(MapPackageName) / 100.0f;
	//UE_LOG(LogTemp, Warning, TEXT("LoadPercent=%f"), LoadPercent);
	if (LoadPercent >= 1.0f)
	{
		GetWorld()->GetTimerManager().ClearTimer(ProgressTimerHandle);
	}
}