// Fill out your copyright notice in the Description page of Project Settings.


#include "ArcadeSoundTriggerVolume.h"
#include "Components/BoxComponent.h"
#include "Components/AudioComponent.h"
#include "Sound/SoundBase.h"

#include "MetasoundSource.h"
#include "Kismet/GameplayStatics.h"

// Sets default values
AArcadeSoundTriggerVolume::AArcadeSoundTriggerVolume()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	TriggerVolume = CreateDefaultSubobject<UBoxComponent>(TEXT("TriggerVolume"));
	RootComponent = TriggerVolume;
	TriggerVolume->OnComponentBeginOverlap.AddDynamic(this, &AArcadeSoundTriggerVolume::OnTriggerOverlapBegin);
	TriggerVolume->OnComponentEndOverlap.AddDynamic(this, &AArcadeSoundTriggerVolume::OnTriggerOverlapEnd);

	AudioControl = CreateDefaultSubobject<UAudioComponent>(TEXT("AudioConntrol"));
	AudioControl->SetupAttachment(RootComponent);
}

// Called when the game starts or when spawned
void AArcadeSoundTriggerVolume::BeginPlay()
{
	Super::BeginPlay();

	if (SoundProcessor)
	{
		AudioControl->SetSound(SoundProcessor);
	}

	if (!Sounds.IsEmpty())
	{
		for (USoundBase* sound : Sounds)
		{
			SoundSources.Add(sound);
		}
	}
	
}

void AArcadeSoundTriggerVolume::OnTriggerOverlapBegin(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	if (OtherActor->IsA(PlayerToDetect))
	{
		if (!Sounds.IsEmpty())
		{
			AudioControl->SetObjectArrayParameter(FName("Sounds"), SoundSources);
			AudioControl->SetBoolParameter(FName("Loop"), bShouldLoop);
			AudioControl->SetFloatParameter(FName("Pitch Shift Min"), PitchShiftMin);
			AudioControl->SetFloatParameter(FName("Pitch Shift Max"), PitchShiftMax);
			AudioControl->SetIntParameter(FName("Sound Repeats"), MaxIndividualRepeats);

			AudioControl->Play();
		}
	}
}

void AArcadeSoundTriggerVolume::OnTriggerOverlapEnd(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{
	AudioControl->Stop();
}

