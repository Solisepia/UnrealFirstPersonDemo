// Copyright Epic Games, Inc. All Rights Reserved.

#include "MyFirstPGameMode.h"
#include "MyFirstPCharacter.h"
#include "MyFirstPPlayerController.h"
#include "UObject/ConstructorHelpers.h"
#include "MyPlayerState.h"
#include "Kismet/GameplayStatics.h"

AMyFirstPGameMode::AMyFirstPGameMode()
	: Super(), CountDownTime(60)
{
	// set default pawn class to our Blueprinted character
	static ConstructorHelpers::FClassFinder<APawn> PlayerPawnClassFinder(TEXT("/Game/FirstPerson/Blueprints/BP_FirstPersonCharacter"));
	DefaultPawnClass = PlayerPawnClassFinder.Class;
	PlayerStateClass = AMyPlayerState::StaticClass();
}

void AMyFirstPGameMode::BeginPlay()
{
	Super::BeginPlay();

	GetWorldTimerManager().SetTimer(CountDownTimer, this, &AMyFirstPGameMode::CountDownTimerTick, 1.0f, true);
}

void AMyFirstPGameMode::CountDownTimerTick()
{
	if (AMyPlayerState* PlayerState = Cast<AMyPlayerState>(UGameplayStatics::GetPlayerState(GetWorld(),0)))
	{
		if (PlayerState->CurrentHealth > 0 && CountDownTime > 0)
		{
			CountDownTime--;
		}
		else
		{
			EndGame();
		}
	}
}

void AMyFirstPGameMode::EndGame()
{
	GetWorldTimerManager().ClearTimer(CountDownTimer);
	
	PauseGame();
	OnEndGameBlueprint();
}

void AMyFirstPGameMode::PauseGame()
{
	UGameplayStatics::SetGlobalTimeDilation(GetWorld(),0.0f);

	for (FConstPlayerControllerIterator it = GetWorld()->GetPlayerControllerIterator(); it; ++it)
	{
		AMyFirstPPlayerController *PlayerController = Cast<AMyFirstPPlayerController>( it->Get() );
		if (PlayerController)
		{
			PlayerController->SetInputMode(FInputModeUIOnly());
			PlayerController->bShowMouseCursor = true;
		}
	}
}

void AMyFirstPGameMode::RestartGame()
{
	for (FConstPlayerControllerIterator it = GetWorld()->GetPlayerControllerIterator(); it; ++it)
	{
		AMyFirstPPlayerController *PlayerController = Cast<AMyFirstPPlayerController>( it->Get() );
		if (PlayerController)
		{
			PlayerController->SetInputMode(FInputModeGameOnly());
			PlayerController->bShowMouseCursor = false;
		}
	}
}
