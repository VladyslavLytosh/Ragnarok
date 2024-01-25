// Copyright by Suspended Team.


#include "AbilitySystem/Abilities/BaseWeaponAbility.h"
#include "Player/PlayerCharacter.h"

UBaseWeaponInstance* UBaseWeaponAbility::GetCurrentEquippedWeaponInstance() const
{
	if (const IWeaponHolderInterface* WeaponHolderInterface = Cast<IWeaponHolderInterface>(GetCurrentAbilityInfo().AvatarPawn))
	{
		return WeaponHolderInterface->GetCurrentEquippedWeapon();
	}
	
	return nullptr;
}
