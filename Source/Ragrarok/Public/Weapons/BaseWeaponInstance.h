// Copyright by Suspended Team.

#pragma once

#include "CoreMinimal.h"
#include "UObject/Object.h"
#include "BaseWeaponInstance.generated.h"

USTRUCT(BlueprintType)
struct FWeaponData
{
	GENERATED_BODY()

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Weapon name")
	FName WeaponName;

	UPROPERTY(EditDefaultsOnly, Category = "Category", meta=(AllowPrivateAccess=true))
	FText WeaponDisplayName;

	int32 FireRate;

};

USTRUCT(BlueprintType)
struct FWeaponVisualData
{
	GENERATED_BODY()

	
	
};
UCLASS()
class RAGRAROK_API UBaseWeaponInstance : public UObject
{
	GENERATED_BODY()

	UPROPERTY(EditDefaultsOnly, Category = "Weapon data")
	FWeaponData WeaponData;
};
