// Copyright by Suspended Team.

#pragma once

#include "CoreMinimal.h"
#include "RagnarokGlobals.generated.h"

class UPaperSprite;
class UPaperZDAnimSequence;

USTRUCT(BlueprintType)
struct FDeathData
{
	GENERATED_BODY()

	UPROPERTY(EditDefaultsOnly,BlueprintReadOnly)
	UPaperZDAnimSequence* DeathAnimation;

	UPROPERTY(EditDefaultsOnly,BlueprintReadOnly)
	UPaperSprite* DeathSprite;
	
	bool IsValid() const {return DeathAnimation && DeathSprite;}
};
