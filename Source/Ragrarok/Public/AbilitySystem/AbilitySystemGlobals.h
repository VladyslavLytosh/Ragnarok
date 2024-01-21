// Copyright by Suspended Team.

#pragma once

#include "CoreMinimal.h"
#include "AbilitySystemGlobals.generated.h"

class UAbilityBase;
class APawn;
class UAbilitySystemComponent;

//TODO: Rename
USTRUCT(Blueprintable)
struct FAbilityClass
{
	GENERATED_BODY()

	UPROPERTY(EditDefaultsOnly)
	TSubclassOf<UAbilityBase> AbilityClass;

	UPROPERTY(EditDefaultsOnly)
	bool bAutoActivate = false;
};

USTRUCT(Blueprintable)
struct FAbilityInfo
{
	GENERATED_BODY()
	
	UPROPERTY()
	APawn* AvatarPawn;
	
	UPROPERTY()
	UAbilitySystemComponent* AbilitySystemComponent;
};

UENUM(BlueprintType)
enum class EAbilityActivationPolicy : uint8
{
	// Try to activate the ability when the input is triggered.
	OnInputTriggered,

	// Continually try to activate the ability while the input is active.
	WhileInputActive,
};