﻿// Copyright by Suspended Team.

#pragma once

#include "CoreMinimal.h"
#include "AbilitySystemGlobals.h"
#include "GameplayTagContainer.h"
#include "UObject/Object.h"
#include "AbilityBase.generated.h"

/**
 * Base ability class
 */
UCLASS(Abstract,BlueprintType,Blueprintable)
class RAGRAROK_API UAbilityBase : public UObject
{
	GENERATED_BODY()

public:
	void SetAbilityInfo(const FAbilityInfo& NewAbilityInfo) {AbilityInfo = NewAbilityInfo;}
	const FAbilityInfo& GetCurrentAbilityInfo() const {return AbilityInfo;}

	const FGameplayTagContainer& GetAbilityInputTags() const {return AbilityInputTags;}
	bool HasInputTag(const FGameplayTag& GameplayTag) const;
	
	void InputPressed();
	void InputReleased();
	
	void TryActivateAbility(const FAbilityInfo& ActivationInfo);
	
	virtual bool CanActivateAbility(const FAbilityInfo& ActivationInfo);

	virtual void OnAbilityRemoved();
	bool IsAbilityActive() const {return bIsAbilityActive;}

	UFUNCTION(BlueprintPure)
	TEnumAsByte<EAbilityActivationPolicy> GetAbilityActivationPolicy() const {return AbilityActivationPolicy;}
	
protected:
	UPROPERTY(EditDefaultsOnly,Category="Tags")
	FGameplayTagContainer ActivationBlockedTags;

	UPROPERTY(EditDefaultsOnly,Category="Input")
	FGameplayTagContainer AbilityInputTags;

	UPROPERTY(EditDefaultsOnly,Category="Input")
	TEnumAsByte<EAbilityActivationPolicy> AbilityActivationPolicy;
	
	UPROPERTY(EditDefaultsOnly, Category = "Cooldown")
	TEnumAsByte<EAbilityCooldownType> AbilityCooldownType;
	UPROPERTY(EditDefaultsOnly, Category = "Cooldown",meta=(EditCondition="AbilityCooldownType != EAbilityCooldownType::None"))
	float CooldownRate;
	
	virtual void ActivateAbility(const FAbilityInfo& ActivationInfo);
	UFUNCTION(BlueprintImplementableEvent)
	void K2_ActivateAbility(const FAbilityInfo& ActivationInfo);
	
	UFUNCTION(BlueprintCallable)
	virtual void EndAbility();

	UFUNCTION()
	virtual void OnCooldownStarted();
	UFUNCTION()
	virtual void OnCooldownEnded();

private:
	FAbilityInfo AbilityInfo;
	
	bool bIsAbilityActive;

	FTimerHandle CooldownTimerHandle;
};
