// Copyright by Suspended Team.

#pragma once

#include "CoreMinimal.h"
#include "RagnarokGlobals.generated.h"

class UPaperFlipbook;

USTRUCT(BlueprintType)
struct FDeathData
{
	GENERATED_BODY()

	UPROPERTY(EditDefaultsOnly,BlueprintReadOnly)
	UPaperFlipbook* DeathFlipbook;
};
