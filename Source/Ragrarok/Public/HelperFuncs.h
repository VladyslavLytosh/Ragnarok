// Copyright by Suspended Team.

#pragma once

#include "CoreMinimal.h"
#include "Kismet/BlueprintFunctionLibrary.h"
#include "HelperFuncs.generated.h"

UCLASS()
class RAGRAROK_API UHelperFuncs : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()
	
public:	
	UFUNCTION(BlueprintPure, BlueprintCallable, Category = "Object")
	static UObject* GetDefaultObject(TSubclassOf<UObject> ObjectClass);
};
