// Copyright by Suspended Team.

#pragma once

#include "CoreMinimal.h"
#include "RagnarokGlobals.h"
#include "Engine/DataAsset.h"
#include "CharacterDeathData.generated.h"


/**
 * Death Animations data asset. Contains related to damage type death data
 */
UCLASS()
class RAGRAROK_API UCharacterDeathData : public UDataAsset
{
	GENERATED_BODY()

public:
	FDeathData GetDeathDataByDamageType(const TSubclassOf<UDamageType>& DamageType);
private:
	TMap<TSubclassOf<UDamageType>,FDeathData> Data;
};
