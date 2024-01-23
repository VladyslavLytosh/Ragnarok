// Copyright by Suspended Team.


#include "CharacterClassSystem/CharacterClass.h"

#include "AbilitySystem/AbilitySet.h"
#include "AbilitySystem/AbilitySystemComponent.h"
#include "PaperZDAnimationComponent.h"
#include "PaperZDAnimInstance.h"
#include "Characters/BaseCharacter.h"
#include "Weapons/BaseWeaponInstance.h"

void UCharacterClass::OnClassChanged(ABaseCharacter* Character)
{
	if (!Character)
	{
		return;
	}
	UAbilitySystemComponent* AbilitySystemComponent = Character->GetAbilitySystemComponent();
	UPaperZDAnimationComponent* PaperZdAnimationComponent = Character->GetAnimationComponent();
	
	if (AbilitySet && AnimInstanceClass && AbilitySystemComponent && PaperZdAnimationComponent)
	{
		AbilitySystemComponent->GiveToAbilitySystem(AbilitySet->AbilitiesToGrant);
		PaperZdAnimationComponent->SetAnimInstanceClass(AnimInstanceClass);
		if (CharacterWeaponClass)
		{
			Character->SetCurrentEquippedWeapon(CharacterWeaponClass);
		}
	}
}
