// Fill out your copyright notice in the Description page of Project Settings.


#include "ArcadeController.h"
#include "EnhancedInputComponent.h"
#include "EnhancedInputSubsystems.h"
#include "InputActionValue.h"
#include "Engine/LocalPlayer.h"

bool AArcadeController::ArcadeRemoveInputMapping(UInputMappingContext* removedMapping)
{
	bool bSuccess = false;

	if (UEnhancedInputLocalPlayerSubsystem* Subsystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(GetLocalPlayer()))
	{
		if (Subsystem->HasMappingContext(removedMapping))
		{
			Subsystem->RemoveMappingContext(removedMapping);
			bSuccess = true;
		}
	}

	return bSuccess;
}

bool AArcadeController::ArcadeAddInputMapping(UInputMappingContext* addedMapping, int32 priority)
{
	bool bSuccess = false;

	if (UEnhancedInputLocalPlayerSubsystem* Subsystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(GetLocalPlayer()))
	{
		if (!Subsystem->HasMappingContext(addedMapping))
		{
			Subsystem->AddMappingContext(addedMapping, priority + 1);
			bSuccess = true;
		}
	}

	return bSuccess;
}

void AArcadeController::ArcadeRemoveAllMappings()
{
	if (UEnhancedInputLocalPlayerSubsystem* Subsystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(GetLocalPlayer()))
	{
		Subsystem->ClearAllMappings();

		if (ArcadeHubMapping != nullptr)
		{
			Subsystem->AddMappingContext(ArcadeHubMapping, 0);
		}
	}
}

void AArcadeController::SetupInputComponent()
{
	Super::SetupInputComponent();

	if (UEnhancedInputComponent* EnhancedInput = Cast<UEnhancedInputComponent>(InputComponent))
	{
		if (ArcadeHubPauseAction != nullptr)
		{
			EnhancedInput->BindAction(ArcadeHubPauseAction, ETriggerEvent::Started, this, &AArcadeController::ArcadeHubPause);
		}
	}
}

void AArcadeController::BeginPlay()
{
	Super::BeginPlay();

}

void AArcadeController::OnPossess(APawn* aPawn)
{
	Super::OnPossess(aPawn);

	if (UEnhancedInputLocalPlayerSubsystem* Subsystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(GetLocalPlayer()))
	{
		if (ArcadeHubMapping != nullptr)
		{
			Subsystem->AddMappingContext(ArcadeHubMapping, 0);
		}

		if (GameMapping.Num() > 0)
		{
			UE_LOG(LogTemp, Warning, TEXT("Additionalmappings found"));
			for (int i = 0; i < GameMapping.Num(); i++)
			{
				UE_LOG(LogTemp, Warning, TEXT("Additionalmapping Added"));
				Subsystem->AddMappingContext(GameMapping[i], i + 1);
			}
		}
	}
}

void AArcadeController::ArcadeHubPause_Implementation(const FInputActionValue& Value)
{
	// Do nothing
}
