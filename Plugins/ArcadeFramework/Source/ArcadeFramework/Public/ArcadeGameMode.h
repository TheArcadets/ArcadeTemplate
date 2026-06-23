#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "ArcadeGameMode.generated.h"

UCLASS()

class ARCADEFRAMEWORK_API AArcadeGameMode : public AActor
{
	GENERATED_BODY()

protected:

	virtual void BeginPlay() override;

public:

	AArcadeGameMode();

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Custom|GameMode", meta = (ToolTip = "Choose the pawn to be as your player character in here."))
	TSubclassOf<APawn> PlayerPawn;

	//UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Custom|GameMode")
	//TSubclassOf<APlayerController> PlayerController;

	// Used for spawn tags if the level streamed contains multiple player spawns
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Custom|GameMode", meta = (ToolTip = "Check this if you have multiple PlayerStarts in your level and need to use the PlayerStartTag variable on them to select a spawn. NOTE: This will be overwritten by your CabinetDataAsset."))
	bool useSpawnTag;

	// Spawn tag
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Custom|GameMode", meta = (EditCondition = "useSpawnTag", EditConditionHides, ToolTip = "Place your PlayerStartTag value in here. NOTE: This will be overwritten by your CabinetDataAsset"))
	FName spawnTag;

	UFUNCTION()
	void EndGameCleanup();

private:

	void SpawnPlayer();

};