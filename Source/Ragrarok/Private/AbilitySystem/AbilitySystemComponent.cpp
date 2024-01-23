// Copyright by Suspended Team.


#include "AbilitySystem/AbilitySystemComponent.h"

#include "AbilitySystem/AbilityBase.h"


void UAbilitySystemComponent::AddGameplayTag(FGameplayTag GameplayTag)
{
	AbilityTagsContainer.AddTag(GameplayTag);
}

void UAbilitySystemComponent::RemoveGameplayTags(const FGameplayTagContainer& GameplayTagContainer)
{
	AbilityTagsContainer.RemoveTags(GameplayTagContainer);
}


bool UAbilitySystemComponent::HasTag(const FGameplayTag& GameplayTag) const
{
	return AbilityTagsContainer.HasTag(GameplayTag);
}

void UAbilitySystemComponent::GiveToAbilitySystem(const TArray<FAbilityClass>& AbilitiesToGrant)
{
	if (AbilitiesToGrant.Num() <= 0)
	{
		return;
	}

	for (const FAbilityClass& AbilityClass : AbilitiesToGrant)
	{
		if (!CurrentAbilities.Contains(AbilityClass.AbilityClass))
		{
			FAbilityInfo AbilityInfo;
			AbilityInfo.AvatarPawn = GetPawn<APawn>();
			AbilityInfo.AbilitySystemComponent = this;
			
			UAbilityBase* NewAbility = NewObject<UAbilityBase>(this,AbilityClass.AbilityClass);
			NewAbility->SetAbilityInfo(AbilityInfo);
			
			CurrentAbilities.Add(AbilityClass.AbilityClass,NewAbility);
			
			if (AbilityClass.bAutoActivate)
			{
				NewAbility->TryActivateAbility(AbilityInfo);
			}
		}
	}
}

void UAbilitySystemComponent::TakeFromAbilitySystem(const TArray<FAbilityClass>& AbilitiesToRemove)
{
	if (AbilitiesToRemove.Num() <= 0)
	{
		return;
	}
	
	for (const FAbilityClass& AbilityClass : AbilitiesToRemove)
	{
		if (CurrentAbilities.Contains(AbilityClass.AbilityClass))
		{
			UAbilityBase* AbilityToRemove = CurrentAbilities[AbilityClass.AbilityClass];
			CurrentAbilities.Remove(AbilityClass.AbilityClass);

			AbilityToRemove->OnAbilityRemoved();
		}
	}
}

void UAbilitySystemComponent::AbilityInputTagPressed(const FGameplayTag& InputTag)
{
	if (!InputTag.IsValid())
	{
		return;
	}
	
	for (const TPair<TSubclassOf<UAbilityBase>,UAbilityBase*>& Pair : CurrentAbilities)
	{
		if (Pair.Value && Pair.Value->HasInputTag(InputTag))
		{
			InputPressedAbilities.AddUnique(Pair.Value);
			InputHeldAbilities.AddUnique(Pair.Value);
		}
	}
}

void UAbilitySystemComponent::AbilityInputTagReleased(const FGameplayTag& InputTag)
{
	if (!InputTag.IsValid())
	{
		return;
	}
	
	for (const TPair<TSubclassOf<UAbilityBase>,UAbilityBase*>& Pair : CurrentAbilities)
	{
		if (Pair.Value && Pair.Value->HasInputTag(InputTag))
		{
			InputReleasedAbilities.AddUnique(Pair.Value);
			InputHeldAbilities.Remove(Pair.Value);
		}
	}
}

void UAbilitySystemComponent::ProcessAbilityInput(float DeltaTime, bool bGamePaused)
{
	static TArray<UAbilityBase*> AbilitiesToActivate;
	AbilitiesToActivate.Reset();

	for (const TWeakObjectPtr<UAbilityBase>& Ability : InputHeldAbilities)
	{
		if (Ability.IsValid() && Ability.Get() && !Ability->IsAbilityActive())
		{
			if (Ability->GetAbilityActivationPolicy() == EAbilityActivationPolicy::WhileInputActive)
			{
				AbilitiesToActivate.AddUnique(Ability.Get());
			}
		}
	}

	for (const TWeakObjectPtr<UAbilityBase>& Ability : InputPressedAbilities)
	{
		if (Ability.IsValid() && Ability.Get())
		{
			if (Ability->IsAbilityActive())
			{
				Ability->InputPressed();
			}
			else
			{
				if (Ability->GetAbilityActivationPolicy() == EAbilityActivationPolicy::OnInputTriggered)
				{
					AbilitiesToActivate.AddUnique(Ability.Get());
				}
			}
		}
	}

	for (UAbilityBase* Ability : AbilitiesToActivate)
	{
		TryActivateAbility(Ability);
	}

	for (const TWeakObjectPtr<UAbilityBase>& Ability : InputReleasedAbilities)
	{
		if (Ability.IsValid() && Ability.Get() && Ability->IsAbilityActive())
		{
			Ability->InputReleased();
		}
	}

	InputPressedAbilities.Reset();
	InputReleasedAbilities.Reset();
}

void UAbilitySystemComponent::TryActivateAbility(UAbilityBase* AbilityBase)
{
	if (!AbilityBase) return;
	
	FAbilityInfo AbilityInfo;
	AbilityInfo.AvatarPawn = GetPawn<APawn>();
	AbilityInfo.AbilitySystemComponent = this;

	AbilityBase->SetAbilityInfo(AbilityInfo);
	AbilityBase->TryActivateAbility(AbilityInfo);
}
