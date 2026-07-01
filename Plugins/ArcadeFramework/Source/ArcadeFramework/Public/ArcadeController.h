// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "ArcadeController.generated.h"


class UInputMappingContext;
class UInputAction;
struct FInputActionValue;
/**
 * 
 */
UCLASS()
class ARCADEFRAMEWORK_API AArcadeController : public APlayerController
{
	GENERATED_BODY()

public:


	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "00_Input")
	TArray<UInputMappingContext*> GameMapping;
	

private:
	UPROPERTY()
	UInputMappingContext* ArcadeHubMapping;

	UPROPERTY()
	UInputAction* ArcadeHubPauseAction;

protected:

	virtual void SetupInputComponent() override;
	virtual void BeginPlay() override;
	virtual void OnPossess(APawn* aPawn) override;

	UFUNCTION(BlueprintNativeEvent)
	void ArcadeHubPause(const FInputActionValue& Value);
};
