// Copyright by Suspended Team.


#include "AbilitySystem/AbilityBase.h"

#include "AbilitySystem/AbilitySystemComponent.h"

bool UAbilityBase::HasInputTag(const FGameplayTag& GameplayTag) const
{
	return AbilityInputTags.HasTag(GameplayTag);
}

void UAbilityBase::InputPressed()
{
}

void UAbilityBase::InputReleased()
{
}

void UAbilityBase::TryActivateAbility(const FAbilityInfo& ActivationInfo)
{
	if (CanActivateAbility(ActivationInfo))
	{
		ActivateAbility(ActivationInfo);
	}
}

void UAbilityBase::ActivateAbility(const FAbilityInfo& ActivationInfo)
{
	bIsAbilityActive = true;
	K2_ActivateAbility(ActivationInfo);
}

bool UAbilityBase::CanActivateAbility(const FAbilityInfo& ActivationInfo)
{
	return ActivationInfo.AvatarPawn && ActivationInfo.AbilitySystemComponent && !ActivationInfo.AbilitySystemComponent->GetAbilityTags().HasAny(ActivationBlockedTags);
}

void UAbilityBase::EndAbility()
{
	bIsAbilityActive = false;
}

void UAbilityBase::OnAbilityRemoved()
{
}
