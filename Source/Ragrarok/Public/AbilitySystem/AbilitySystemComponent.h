// Copyright by Suspended Team.

#pragma once

#include "CoreMinimal.h"
#include "GameplayTagContainer.h"
#include "Components/PawnComponent.h"
#include "AbilitySystemGlobals.h"
#include "AbilitySystemComponent.generated.h"

class UAbilityBase;

/**
 * Ability system component class
 */
UCLASS(BlueprintType,Blueprintable, Meta=(BlueprintSpawnableComponent))
class RAGRAROK_API UAbilitySystemComponent : public UPawnComponent
{
	GENERATED_BODY()
public:
	UFUNCTION(BlueprintPure)
	const FGameplayTagContainer& GetAbilityTags() const {return AbilityTagsContainer;}

	UFUNCTION(BlueprintCallable)
	void AddGameplayTag(FGameplayTag GameplayTag);
	UFUNCTION(BlueprintCallable)
	void RemoveGameplayTags(const FGameplayTagContainer& GameplayTagContainer);
	
	UFUNCTION(BlueprintPure)
	bool HasTag(const FGameplayTag& GameplayTag) const;

	void GiveToAbilitySystem(const TArray<FAbilityClass>& AbilitiesToGrant);
	void TakeFromAbilitySystem(const TArray<FAbilityClass>& AbilitiesToRemove);
	
	void AbilityInputTagPressed(const FGameplayTag& InputTag);
	void AbilityInputTagReleased(const FGameplayTag& InputTag);

	void ProcessAbilityInput(float DeltaTime, bool bGamePaused);

	UFUNCTION(BlueprintCallable)
	void TryActivateAbilityByClass(TSubclassOf<UAbilityBase> AbilityClass);
	
protected:
	void TryActivateAbility(UAbilityBase* AbilityBase);

	UFUNCTION(BlueprintPure)
	UAbilityBase* GetFirstShouldDisplayOnUIAbility();
	
private:
	UPROPERTY(BlueprintReadOnly, meta=(AllowPrivateAccess = true))
	TMap<TSubclassOf<UAbilityBase>,UAbilityBase*> CurrentAbilities;

	TArray<TWeakObjectPtr<UAbilityBase>> InputPressedAbilities;
	TArray<TWeakObjectPtr<UAbilityBase>> InputReleasedAbilities;
	TArray<TWeakObjectPtr<UAbilityBase>> InputHeldAbilities;

	UPROPERTY()
	FGameplayTagContainer AbilityTagsContainer;
};
