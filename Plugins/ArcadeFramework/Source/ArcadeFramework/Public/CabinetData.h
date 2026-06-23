// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/DataAsset.h"
#include "ArcadeGameMode.h"
#include "CabinetData.generated.h"


UENUM(BlueprintType)
enum EGenreTypes
{
	Horror UMETA(DisplayName = "Horror"),
	Action UMETA(DisplayName = "Action"),
	Adventure UMETA(DisplayName = "Adventure"),
	Fighting UMETA(DisplayName = "Fighting"),
	Puzzle UMETA(DisplayName = "Puzzle"),
	RTS UMETA(DisplayName = "RTS"),
	Roguelike UMETA(DisplayName = "Roguelike"),
	Sports UMETA(DisplayName = "Sports"),
	RPG UMETA(DisplayName = "RPG"),
	Strategy UMETA(DisplayName = "Strategy"),
	Casual UMETA(DisplayName = "Casual"),
	FPS UMETA(DisplayName = "FPS"),
	Other UMETA(DispalyName = "Other")
};
/**
 * 
 */
UCLASS()
class ARCADEFRAMEWORK_API UCabinetData : public UDataAsset
{
	GENERATED_BODY()
	
public:

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Team Info", meta = (ToolTip="Place the name of each developer that worked on the game in here."))
	TArray<FString> TeamMembers;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Team Info", meta = (ToolTip="The team name for this game."))
	FString TeamName;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Game Info", meta = (ToolTip = "Place the game's title here."))
	FText GameTitle;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Game Info", meta = (
		ToolTip = "Place the game's max number of player's here. NOTE: Currently locked to 1 until multiplayer support is added.",
		ClampMin=1, ClampMax=1, UIMin=1, UIMax=1
		))
	int32 MaxPlayers = 1;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Game Info", meta = (MultiLine=true, ToolTip="Place a description of your game in here. To add a line break press Shift+enter"))
	FText Description;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Game Info", meta = (ToolTip = "Select a genre. If you choose 'Other' an option will open to allow a manual value"))
	TEnumAsByte<EGenreTypes> GameGenre;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Game Info", meta = (EditCondition = "GameGenre == EGenreTypes::Other", EditConditionHides))
	FString OtherGenre;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Cabinet Customization", meta = (ToolTip = "The cabinet mesh that should be used to display your game in the arcade."))
	UStaticMesh* CabinetType;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Cabinet Customization", meta = (ToolTip = "An icon to represent your game. Will show on the cabinet screen."))
	UTexture2D* GameIcon;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Cabinet Customization", meta = (ToolTip = "Place any custom cabinet textures for the front here."))
	UTexture2D* CabinetFront;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Cabinet Customization", meta = (ToolTip = "Place any custom cabinet textures for the sides here."))
	UTexture2D* CabinetSides;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Launch Info", meta = (ToolTip = "Select the map that your game should start with."))
	UWorld* InitialGameMap;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Launch Info", meta = (ToolTip = "If you have multiple player start locations and you need to assign a start tag check this."))
	bool UseStartTag;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Launch Info", meta = (EditCondition = "UseStartTag", EditConditionHides, ToolTip="Place the start tag here."))
	FName StartTag;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Launch Info", meta = (ToolTip = "Choose the GameMode used for the game here."))
	TSubclassOf<AArcadeGameMode> GameModeClass;

	//UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Launch Info", meta = (ToolTip = "Check this if the default hub controls are needed."))
	//bool UseHubController;

	//UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Launch Info", meta = (ToolTip = "Choose the player controller to be used for the game here."))
	//TSubclassOf<AController> PlayerControllerClass;
	
	//UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Launch Info", meta = (ToolTip = "Choose the player class to be used for the game here."))
	//TSubclassOf<APawn> PlayerPawnClass;
};
