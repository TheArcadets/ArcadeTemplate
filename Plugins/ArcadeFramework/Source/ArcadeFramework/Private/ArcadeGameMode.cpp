#include "ArcadeGameMode.h"
#include "GameFramework/PlayerStart.h"
#include "Kismet/GameplayStatics.h"
#include "Engine/World.h"
#include "ArcadeFramework/Public/ArcadeInstance.h"
#include "GameFramework/Pawn.h"
#include "ArcadeController.h"
#include "GameFramework/GameMode.h"

AArcadeGameMode::AArcadeGameMode()
{
	// Constructor
}

void AArcadeGameMode::BeginPlay()
{
	Super::BeginPlay();

	SpawnPlayer();
}

void AArcadeGameMode::EndGameCleanup()
{
}

// Helper Function to make it easier to use the custom ArcadeInstance for dynamic variables
UArcadeInstance* AArcadeGameMode::GetArcadeGameInstance()
{
	if (UArcadeInstance* GameInstance = Cast<UArcadeInstance>(UGameplayStatics::GetGameInstance(GetWorld())))
	{
		return GameInstance;
	}
	else
	{
		return nullptr;
	}
}

// Spawns in the player pawn and posses them at the given spawn location
void AArcadeGameMode::SpawnPlayer()
{
	APlayerStart* spawnLocation = nullptr;

	TArray<AActor*> playerStarts;
	UGameplayStatics::GetAllActorsOfClass(GetWorld(), APlayerStart::StaticClass(), playerStarts);



	// Checks for a specific spawn tag if needed. Otherwise avoids the arcade hub's default spawn tag of ARCADESPAWN
	if (useSpawnTag)
	{
		for (int i = 0; i < playerStarts.Num(); i++)
		{
			APlayerStart* startOption = Cast<APlayerStart>(playerStarts[i]);

			if (startOption->PlayerStartTag == spawnTag)
			{
				spawnLocation = startOption;
			}
		}
	}
	else
	{
		for (int i = 0; i < playerStarts.Num(); i++)
		{
			APlayerStart* startOption = Cast<APlayerStart>(playerStarts[i]);

			if (startOption->PlayerStartTag != FName("ARCADESPAWN"))
			{
				spawnLocation = startOption;
			}
		}
	}

	if (spawnLocation)
	{
		//APawn* spawnedPlayer = GetWorld()->SpawnActor<APawn>(PlayerPawn, spawnLocation->GetActorTransform());

		//UGameplayStatics::GetPlayerController(GetWorld(), 0)->Possess(spawnedPlayer);
		if (PlayerController != nullptr)
		{
			APlayerController* OldController = UGameplayStatics::GetPlayerController(GetWorld(), 0);
			FActorSpawnParameters SpawnParams;
			SpawnParams.Owner = OldController->GetOwner();
			SpawnParams.Instigator = OldController->GetInstigator();

			AArcadeController* NewController = GetWorld()->SpawnActor<AArcadeController>(PlayerController, SpawnParams);

			UGameplayStatics::GetGameMode(GetWorld())->SwapPlayerControllers(OldController, NewController);

			APawn* spawnedPlayer = GetWorld()->SpawnActor<APawn>(PlayerPawn, spawnLocation->GetActorTransform());

			NewController->Possess(spawnedPlayer);

			OldController->Destroy();
		}
		else
		{
			APawn* spawnedPlayer = GetWorld()->SpawnActor<APawn>(PlayerPawn, spawnLocation->GetActorTransform());
			UGameplayStatics::GetPlayerController(GetWorld(), 0)->Possess(spawnedPlayer);
		}
	}

}


