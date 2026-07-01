#pragma once

#include "Kismet/BlueprintFunctionLibrary.h"
#include "ArcadeFunctions.generated.h"

UCLASS(BlueprintType)
class ARCADEFRAMEWORK_API UArcadeFunctions : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()

public:

	UFUNCTION(BlueprintCallable, Category = "ArcadeFunctions", meta = (WorldContext = "Context"))
	static void ArcadeOpenLevel(UObject* Context, TSoftObjectPtr<UWorld> LevelToOpen);

	UFUNCTION(BlueprintCallable, Category = "ArcadeFunctions", meta = (WorldContext = "Context"))
	static ULevelStreamingDynamic* ArcadeLoadStreamLevel(UObject* Context, TSoftObjectPtr<UWorld> LevelToStream, FVector StreamLocation);

	UFUNCTION(BlueprintCallable, Category = "ArcadeFunctions", meta = (WorldContext = "Context"))
	static void ArcadeUnloadStreamLevel(UObject* Context, ULevelStreamingDynamic* LevelToUnload);

	UFUNCTION(BlueprintCallable, Category = "ArcadeFunctions", meta = (WorldContext = "Context"))
	static void QuitToHub();

};