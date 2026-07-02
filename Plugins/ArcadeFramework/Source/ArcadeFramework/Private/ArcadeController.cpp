// Fill out your copyright notice in the Description page of Project Settings.


#include "ArcadeController.h"
#include "EnhancedInputComponent.h"
#include "EnhancedInputSubsystems.h"
#include "InputActionValue.h"
#include "Engine/LocalPlayer.h"

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
