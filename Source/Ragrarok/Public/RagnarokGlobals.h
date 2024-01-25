// Copyright by Suspended Team.

#pragma once

#include "CoreMinimal.h"
#include "RagnarokGlobals.generated.h"

class UPaperFlipbook;
class UMaterialInterface;

USTRUCT(BlueprintType)
struct FDeathData
{
	GENERATED_BODY()

	UPROPERTY(EditDefaultsOnly,BlueprintReadOnly)
	UPaperFlipbook* DeathFlipbook;

	UPROPERTY(EditDefaultsOnly,BlueprintReadOnly)
	TArray<UMaterialInterface*> BloodDecals;
};
