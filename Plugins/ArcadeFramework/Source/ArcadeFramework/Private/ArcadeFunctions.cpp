#include "ArcadeFunctions.h"
#include "Kismet/GameplayStatics.h"
#include "Engine/LevelStreamingDynamic.h"
#include "Engine/World.h"

void UArcadeFunctions::ArcadeOpenLevel(UObject* Context, TSoftObjectPtr<UWorld> LevelToOpen)
{
	UE_LOG(LogTemp, Warning, TEXT("Open Level Begun"));
	if (IsValid(Context))
	{
		UE_LOG(LogTemp, Warning, TEXT("Context valid"));
		if (!LevelToOpen.IsNull())
		{

			FString levelPath = LevelToOpen.ToSoftObjectPath().GetLongPackageName();

			UGameplayStatics::OpenLevel(Context, FName(levelPath));

			/*UE_LOG(LogTemp, Warning, TEXT("LevelToOpen Valid"));
			bool levelLoadSuccess;
			FRotator SpawnRotation = FRotator::ZeroRotator;
			FVector TransformOffset = FVector(0, 50000, 500);
			FGuid uniqueIDSuffix = FGuid::NewGuid();
			UE_LOG(LogTemp, Warning, TEXT("LevelPath name %s"), *levelPath);
			FString uniqueLevelName = uniqueIDSuffix.ToString();

			ULevelStreamingDynamic* LoadedLevel = ULevelStreamingDynamic::LoadLevelInstance(Context->GetWorld(), levelPath, TransformOffset, SpawnRotation, levelLoadSuccess, uniqueLevelName);
			UE_LOG(LogTemp, Warning, TEXT("Level Loaded %s"), *uniqueLevelName);
			
			FName SafeName = LoadedLevel->GetWorldAssetPackageFName();
			UE_LOG(LogTemp, Warning, TEXT("Level Safe Name: %s"), *SafeName.ToString());

			const TArray<ULevelStreaming*>& StreamingLevels = Context->GetWorld()->GetStreamingLevels();
			for (ULevelStreaming* LevelStreamed : StreamingLevels)
			{
				FName PIEFixedName = (LevelStreamed->GetWorldAssetPackageFName());
				UE_LOG(LogTemp, Warning, TEXT("LevelStream entry: %s"), *PIEFixedName.ToString());

				if (LevelStreamed && PIEFixedName != SafeName)
				{
					UE_LOG(LogTemp, Warning, TEXT("Level Tagged for unload %s"), *PIEFixedName.ToString());
					LevelStreamed->SetIsRequestingUnloadAndRemoval(true);
				}
			}*/
		}
		else
		{
			UE_LOG(LogTemp, Warning, TEXT("LevelToOpen invalid"));
		}
	}
}

ULevelStreamingDynamic* UArcadeFunctions::ArcadeLoadStreamLevel(UObject* Context, TSoftObjectPtr<UWorld> LevelToStream, FVector StreamLocation)
{
	if (IsValid(Context))
	{
		if (!LevelToStream.IsNull())
		{
			FString levelPath = LevelToStream.ToSoftObjectPath().GetLongPackageName();
			bool levelLoadSuccess;
			FRotator SpawnRotation = FRotator::ZeroRotator;
			FVector TransformOffset = FVector(0, 0, 0) + StreamLocation;
			FGuid uniqueIDSuffix = FGuid::NewGuid();
			FString uniqueLevelName = uniqueIDSuffix.ToString();

			ULevelStreamingDynamic* LoadedLevel = ULevelStreamingDynamic::LoadLevelInstance(Context->GetWorld(), levelPath, TransformOffset, SpawnRotation, levelLoadSuccess, uniqueLevelName);

			return LoadedLevel;
		}
		else
		{
			return nullptr;
		}
	}
	else
	{
		return nullptr;
	}
}

void UArcadeFunctions::ArcadeUnloadStreamLevel(UObject* Context, ULevelStreamingDynamic* LevelToUnload)
{
	if (IsValid(Context))
	{
		if (LevelToUnload)
		{
			LevelToUnload->SetIsRequestingUnloadAndRemoval(true);
		}
	}
}

void UArcadeFunctions::QuitToHub()
{
	UE_LOG(LogTemp, Warning, TEXT("Will quit to hub!"));
	// Do something
}
