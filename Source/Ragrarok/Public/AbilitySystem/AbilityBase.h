// Copyright by Suspended Team.

#pragma once

#include "CoreMinimal.h"
#include "AbilitySystemGlobals.h"
#include "GameplayTagContainer.h"
#include "UObject/Object.h"
#include "AbilityBase.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnAbilityCooldownStarted, float, CooldownRate);

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
	
	virtual void InputPressed();
	virtual void InputReleased();
	
	void TryActivateAbility(const FAbilityInfo& ActivationInfo);
	
	virtual bool CanActivateAbility(const FAbilityInfo& ActivationInfo);

	virtual void OnAbilityRemoved();
	bool IsAbilityActive() const {return bIsAbilityActive;}

	bool ShouldDisplayOnUI() const { return bShouldDisplayOnUI; };

	UFUNCTION(BlueprintPure)
	TEnumAsByte<EAbilityActivationPolicy> GetAbilityActivationPolicy() const {return AbilityActivationPolicy;}

	UPROPERTY(BlueprintAssignable)
	FOnAbilityCooldownStarted OnAbilityCooldownStarted;
	
protected:
	//applies when ability activates
	UPROPERTY(EditDefaultsOnly,Category="Tags")
	FGameplayTagContainer AbilityTags;
	
	UPROPERTY(EditDefaultsOnly,Category="Tags")
	FGameplayTagContainer ActivationBlockedTags;

	UPROPERTY(EditDefaultsOnly,Category="Input")
	FGameplayTagContainer AbilityInputTags;

	UPROPERTY(EditDefaultsOnly,Category="Input")
	TEnumAsByte<EAbilityActivationPolicy> AbilityActivationPolicy;
	
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Cooldown")
	TEnumAsByte<EAbilityCooldownType> AbilityCooldownType;
	
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Cooldown",meta=(Units = "s", EditCondition="AbilityCooldownType != EAbilityCooldownType::None"))
	float CooldownRate;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Cooldown", meta=(EditCondition="AbilityCooldownType != EAbilityCooldownType::None"))
	bool bShouldDisplayOnUI;
	
	virtual void ActivateAbility(const FAbilityInfo& ActivationInfo);
	
	UFUNCTION(BlueprintImplementableEvent)
	void K2_ActivateAbility(const FAbilityInfo& ActivationInfo);
	
	UFUNCTION(BlueprintCallable)
	virtual void EndAbility();

	UFUNCTION()
	virtual void OnCooldownStarted();
	UFUNCTION()
	virtual void OnCooldownEnded();

	//helpers
	UFUNCTION(BlueprintCallable)
	void PlaySoundAtPawnLocation(USoundBase* SoundBase);
	UFUNCTION(BlueprintCallable)
	void PlayCameraShake(TSubclassOf<UCameraShakeBase> CameraShake);
private:
	void AddAbilityTags(UAbilitySystemComponent* AbilitySystemComponent);
	void RemoveAbilityTags(UAbilitySystemComponent* AbilitySystemComponent);
	
	FAbilityInfo AbilityInfo;
	
	bool bIsAbilityActive;

	FTimerHandle CooldownTimerHandle;
};