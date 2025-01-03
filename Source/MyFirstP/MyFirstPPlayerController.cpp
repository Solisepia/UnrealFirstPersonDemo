// Copyright Epic Games, Inc. All Rights Reserved.


#include "MyFirstPPlayerController.h"
#include "EnhancedInputSubsystems.h"
#include "MySaveData.h"
#include "Engine/LocalPlayer.h"
#include "GameFramework/PlayerState.h"
#include "Kismet/GameplayStatics.h"

void AMyFirstPPlayerController::BeginPlay()
{
	Super::BeginPlay();

	// get the enhanced input subsystem
	if (UEnhancedInputLocalPlayerSubsystem* Subsystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(GetLocalPlayer()))
	{
		// add the mapping context so we get controls
		Subsystem->AddMappingContext(InputMappingContext, 0);
	}
	SetInputMode(FInputModeGameOnly());
	bShowMouseCursor = false;
	if (UGameplayStatics::DoesSaveGameExist(TEXT("MySaveDataSlot"),0))
	{
		UMySaveData* DataInstance = Cast<UMySaveData>(UGameplayStatics::LoadGameFromSlot(TEXT("MySaveDataSlot"),0));
		if (DataInstance)
		{
			if (PlayerState)
			{
				PlayerState->SetPlayerName(DataInstance->Username);
			}
		}
	}
}
