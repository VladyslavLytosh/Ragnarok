// Copyright by Suspended Team.


#include "AbilitySystem/Abilities/BaseWeaponAbility.h"

#include "Characters/BaseCharacter.h"

UBaseWeaponInstance* UBaseWeaponAbility::GetCurrentEquippedWeaponInstance() const
{
	if(GetCurrentAbilityInfo().AvatarPawn)
	{
		return Cast<ABaseCharacter>(GetCurrentAbilityInfo().AvatarPawn)->GetCurrentEquippedWeapon();
	}
	return nullptr;
}
