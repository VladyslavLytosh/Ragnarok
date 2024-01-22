// Copyright by Suspended Team.

#pragma once

#include "CoreMinimal.h"
#include "AbilitySystemGlobals.generated.h"

class UAbilityBase;
class APawn;
class UAbilitySystemComponent;

//TODO: Rename
USTRUCT(BlueprintType)
struct FAbilityClass
{
	GENERATED_BODY()

	UPROPERTY(EditDefaultsOnly,BlueprintReadOnly)
	TSubclassOf<UAbilityBase> AbilityClass;

	UPROPERTY(EditDefaultsOnly,BlueprintReadOnly)
	bool bAutoActivate = false;
};

USTRUCT(BlueprintType)
struct FAbilityInfo
{
	GENERATED_BODY()
	
	UPROPERTY(BlueprintReadOnly)
	APawn* AvatarPawn;
	
	UPROPERTY(BlueprintReadOnly)
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

UENUM(BlueprintType)
enum class EAbilityCooldownType : uint8
{
	// Do not apply cooldown
	None,
	
	// Apply cooldown when ability ends
	WhenAbilityEnd,
	
	// Apply cooldown when ability activates
	WhenAbilityActivated
};
