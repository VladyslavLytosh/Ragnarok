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
	AddAbilityTags(GetCurrentAbilityInfo().AbilitySystemComponent);
	if (AbilityCooldownType == EAbilityCooldownType::WhenAbilityActivated)
	{
		if (GetWorld()->GetTimerManager().TimerExists(CooldownTimerHandle))
		{
			UE_LOG(LogTemp,Warning,TEXT("Ability cooldown timer exists during activation"))
			GetWorld()->GetTimerManager().ClearTimer(CooldownTimerHandle);
		}

		OnCooldownStarted();
		GetWorld()->GetTimerManager().SetTimer(CooldownTimerHandle,this,&ThisClass::OnCooldownEnded,CooldownRate);
	}
	K2_ActivateAbility(ActivationInfo);
}

bool UAbilityBase::CanActivateAbility(const FAbilityInfo& ActivationInfo)
{
	const bool bTimerExist = GetWorld()->GetTimerManager().TimerExists(CooldownTimerHandle);
	return ActivationInfo.AvatarPawn && ActivationInfo.AbilitySystemComponent && !ActivationInfo.AbilitySystemComponent->GetAbilityTags().HasAny(ActivationBlockedTags) && !bTimerExist;
}

void UAbilityBase::EndAbility()
{
	bIsAbilityActive = false;
	RemoveAbilityTags(GetCurrentAbilityInfo().AbilitySystemComponent);
	if (AbilityCooldownType == EAbilityCooldownType::WhenAbilityEnd)
	{
		if (GetWorld()->GetTimerManager().TimerExists(CooldownTimerHandle))
		{
			UE_LOG(LogTemp,Warning,TEXT("Ability cooldown timer exists when ability ends"))
			GetWorld()->GetTimerManager().ClearTimer(CooldownTimerHandle);
		}
		
		OnCooldownStarted();
		GetWorld()->GetTimerManager().SetTimer(CooldownTimerHandle,this,&ThisClass::OnCooldownEnded,CooldownRate);
	}
}

void UAbilityBase::OnCooldownStarted()
{
	OnAbilityCooldownStarted.Broadcast(CooldownRate);
}

void UAbilityBase::OnCooldownEnded()
{
}

void UAbilityBase::AddAbilityTags(UAbilitySystemComponent* AbilitySystemComponent)
{
	if (!AbilitySystemComponent) return;
	
	for (const FGameplayTag& Tag : AbilityTags)
	{
		AbilitySystemComponent->AddGameplayTag(Tag);
	}
}

void UAbilityBase::RemoveAbilityTags(UAbilitySystemComponent* AbilitySystemComponent)
{
	if (!AbilitySystemComponent || AbilityTags.Num() <= 0) return;

	AbilitySystemComponent->RemoveGameplayTags(AbilityTags);
}

void UAbilityBase::OnAbilityRemoved()
{
}
