// Copyright by Suspended Team.

#pragma once

#include "CoreMinimal.h"
#include "UObject/Object.h"
#include "AbilitySystemGlobals.h"
#include "AbilitySet.generated.h"

/**
 * Ability set class. Using as data asset for giving and removing abilities
 */
UCLASS(BlueprintType,Blueprintable)
class RAGRAROK_API UAbilitySet : public UDataAsset
{
	GENERATED_BODY()
	
public:
	UPROPERTY(EditDefaultsOnly,Category="Abilities")
	TArray<FAbilityClass> AbilitiesToGrant;
};
