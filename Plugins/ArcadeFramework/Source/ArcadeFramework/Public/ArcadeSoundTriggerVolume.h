// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "ArcadeSoundTriggerVolume.generated.h"

class UBoxComponent;
class UAudioComponent;
class USoundBase;
class UMetaSoundSource;

UCLASS()
class ARCADEFRAMEWORK_API AArcadeSoundTriggerVolume : public AActor
{
	GENERATED_BODY()

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Trigger, meta = (AllowPrivateAccess = "true"))
	UBoxComponent* TriggerVolume;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Audio, meta = (AllowPrivateAccess = "true"))
	UAudioComponent* AudioControl;

public:	
	// Sets default values for this actor's properties
	AArcadeSoundTriggerVolume();

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "00_Audio Options", meta = (ToolTip = "Do not change this from the value assigned by default"))
	UMetaSoundSource* SoundProcessor;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "00_Audio Options")
	bool bShouldLoop;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "00_Audio Options")
	TArray<USoundBase*> Sounds;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "00_Audio Options")
	float PitchShiftMin;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "00_Audio Options")
	float PitchShiftMax;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "00_Audio Options")
	int32 MaxIndividualRepeats;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "00_Audio Options")
	TSubclassOf<AActor> PlayerToDetect;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	UFUNCTION()
	void OnTriggerOverlapBegin(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

	UFUNCTION()
	void OnTriggerOverlapEnd(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex);

private:

	UPROPERTY()
	TArray<UObject*> SoundSources;

};
