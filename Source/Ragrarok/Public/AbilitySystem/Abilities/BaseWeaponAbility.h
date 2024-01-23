// Copyright by Suspended Team.

#pragma once

#include "CoreMinimal.h"
#include "AbilitySystem/AbilityBase.h"
#include "BaseWeaponAbility.generated.h"

class UBaseWeaponInstance;

UCLASS()
class RAGRAROK_API UBaseWeaponAbility : public UAbilityBase
{
	GENERATED_BODY()

protected:
	UBaseWeaponInstance* GetCurrentEquippedWeaponInstance() const;
};
