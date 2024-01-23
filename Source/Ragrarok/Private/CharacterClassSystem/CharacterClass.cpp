// Copyright by Suspended Team.


#include "CharacterClassSystem/CharacterClass.h"

#include "AbilitySystem/AbilitySet.h"
#include "AbilitySystem/AbilitySystemComponent.h"
#include "PaperZDAnimationComponent.h"
#include "PaperZDAnimInstance.h"
#include "Characters/BaseCharacter.h"

void UCharacterClass::OnClassChanged(const ABaseCharacter* Character)
{
	if (!Character)
	{
		return;
	}
	UAbilitySystemComponent* AbilitySystemComponent = Character->GetAbilitySystemComponent();
	UPaperZDAnimationComponent* PaperZdAnimationComponent = Character->GetAnimationComponent();
	
	if (AbilitySet && AnimInstanceClass && AbilitySystemComponent && PaperZdAnimationComponent)
	{
		if (const UCharacterClass* CurrentCharacterClass = Character->GetCurrentCharacterClass())
		{
			if (!CurrentCharacterClass->AbilitySet)
			{
				AbilitySystemComponent->TakeFromAbilitySystem(CurrentCharacterClass->AbilitySet->AbilitiesToGrant);
			}
		}
		AbilitySystemComponent->GiveToAbilitySystem(AbilitySet->AbilitiesToGrant);
		PaperZdAnimationComponent->SetAnimInstanceClass(AnimInstanceClass);
	}
}
