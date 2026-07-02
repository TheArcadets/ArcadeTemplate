// Fill out your copyright notice in the Description page of Project Settings.


#include "ArcadeInstance.h"

DEFINE_FUNCTION(UArcadeInstance::execSaveToInstance)
{
	P_GET_PROPERTY(FStrProperty, Key);

	Stack.MostRecentPropertyAddress = nullptr;
	Stack.MostRecentProperty = nullptr;

	Stack.StepCompiledIn<FProperty>(nullptr);

	void* SrcStructAddress = Stack.MostRecentPropertyAddress;
	FStructProperty* SrcStructProperty = CastField<FStructProperty>(Stack.MostRecentProperty);

	P_FINISH;

	UArcadeInstance* ThisInstance = Cast<UArcadeInstance>(Context);
	if (!ThisInstance) return;

	if (SrcStructAddress && SrcStructProperty && SrcStructProperty->Struct)
	{
		FInstancedStruct NewContainer;
		NewContainer.InitializeAs(SrcStructProperty->Struct, (uint8*)SrcStructAddress);

		ThisInstance->RuntimeData.Emplace(Key, NewContainer);
	}
}

DEFINE_FUNCTION(UArcadeInstance::execLoadFromInstance)
{
	P_GET_PROPERTY(FStrProperty, Key);

	Stack.MostRecentPropertyAddress = nullptr;
	Stack.MostRecentProperty = nullptr;

	Stack.StepCompiledIn<FProperty>(nullptr);

	void* DestStructAddress = Stack.MostRecentPropertyAddress;
	FStructProperty* DestStructProperty = CastField<FStructProperty>(Stack.MostRecentProperty);

	P_FINISH;

	bool bSuccess = false;

	UArcadeInstance* ThisInstance = Cast<UArcadeInstance>(Context);
	if (ThisInstance && DestStructAddress && DestStructProperty && DestStructProperty->Struct)
	{
		if (FInstancedStruct* FoundContainer = ThisInstance->RuntimeData.Find(Key))
		{
			if (FoundContainer->IsValid() && FoundContainer->GetScriptStruct() == DestStructProperty->Struct)
			{
				DestStructProperty->Struct->CopyScriptStruct(DestStructAddress, FoundContainer->GetMemory());
				bSuccess = true;
			}
		}
	}

	*static_cast<bool*>(RESULT_PARAM) = bSuccess;
}

void UArcadeInstance::ClearStruct()
{
	RuntimeData.Reset();
}
