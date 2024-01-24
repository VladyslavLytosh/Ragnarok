// Copyright by Suspended Team.

#pragma once

#include "CoreMinimal.h"
#include "BaseWeaponInstance.h"
#include "WeaponProjectile.h"
#include "ProjectileWeaponInstance.generated.h"

USTRUCT(BlueprintType)
struct FProjectileWeaponData
{
	GENERATED_BODY()

	UPROPERTY(EditDefaultsOnly, Category = "Projectile")
	TSubclassOf<AWeaponProjectile> ProjectileClass;
};

UCLASS()
class RAGRAROK_API UProjectileWeaponInstance : public UBaseWeaponInstance
{
	GENERATED_BODY()

public:
	const FProjectileWeaponData& GetProjectileWeaponData() const { return ProjectileWeaponData; }
	
protected:
	UPROPERTY(EditDefaultsOnly, Category = "Projectile Weapon data")
	FProjectileWeaponData ProjectileWeaponData;
};
