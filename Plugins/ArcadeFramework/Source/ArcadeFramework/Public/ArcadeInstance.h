// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/GameInstance.h"
#include "StructUtils/InstancedStruct.h"
#include "ArcadeInstance.generated.h"

/**
 * 
 */
UCLASS()
class ARCADEFRAMEWORK_API UArcadeInstance : public UGameInstance
{
	GENERATED_BODY()
	
public:
	
	//UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Testing")
	//FInstancedStruct StructData;

	UFUNCTION(BlueprintCallable, CustomThunk, Category = "Arcade Functions", meta = (CustomStructureParam = "Value"))
	void SaveToInstance(const FString& Key, const int32& Value);

	UFUNCTION(BlueprintCallable, CustomThunk, Category = "Arcade Functions", meta = (CustomStructureParam = "OutValue"))
	bool LoadFromInstance(const FString& Key, int32& OutValue);

	DECLARE_FUNCTION(execSaveToInstance);
	DECLARE_FUNCTION(execLoadFromInstance);

	UFUNCTION(BlueprintCallable, Category = "Arcade Functions")
	void ClearStruct();

private:

	UPROPERTY()
	TMap<FString, FInstancedStruct> RuntimeData;

};
