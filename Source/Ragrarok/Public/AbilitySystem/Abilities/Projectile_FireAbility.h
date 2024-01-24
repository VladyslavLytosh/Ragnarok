// Copyright by Suspended Team.

#pragma once

#include "CoreMinimal.h"
#include "BaseWeaponAbility.h"
#include "AbilitySystem/AbilityBase.h"
#include "Projectile_FireAbility.generated.h"

class ABaseCharacter;

UCLASS()
class RAGRAROK_API UProjectile_FireAbility : public UBaseWeaponAbility
{
	GENERATED_BODY()

protected:
	virtual void ActivateAbility(const FAbilityInfo& ActivationInfo) override;

	UFUNCTION()
	void WeaponFire();

	UFUNCTION()
	void OnFireAnimEnded(bool bCompleted);

private:
	FTransform GetProjectileSpawnTransform(const ABaseCharacter* Character) const;
};
