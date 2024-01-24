﻿// Copyright by Suspended Team.

#pragma once

#include "CoreMinimal.h"
#include "UObject/Object.h"
#include "BaseWeaponInstance.generated.h"

class UPaperZDAnimSequence;
class ABaseCharacter;

USTRUCT(BlueprintType)
struct FBaseWeaponData
{
	GENERATED_BODY()

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Weapon name")
	FName WeaponName;

	UPROPERTY(EditDefaultsOnly, Category = "Weapon name", meta=(AllowPrivateAccess=true))
	FText WeaponDisplayName;
	
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category="Weapon|Fire")
	int32 FireRate = 2.0;
};

USTRUCT(BlueprintType)
struct FWeaponVisualData
{
	GENERATED_BODY()
	
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category="Weapon|Fire")
	TObjectPtr<UPaperZDAnimSequence> FireAnimSequence;
};

UCLASS(Blueprintable)
class RAGRAROK_API UBaseWeaponInstance : public UObject
{
	GENERATED_BODY()

public:
	virtual bool CanFire() const;

	void UpdateFiringTime();

	const FBaseWeaponData& GetBaseWeaponData() const { return BaseWeaponData; }

	const FWeaponVisualData& GetWeaponVisualData() const { return WeaponVisualData; }
protected:
	UPROPERTY(EditDefaultsOnly, Category = "Weapon data")
	FBaseWeaponData BaseWeaponData;
	
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category="Weapon|Visual")
	FWeaponVisualData WeaponVisualData;

	ABaseCharacter* GetBaseCharacter() const;

	APawn* GetPawn() const;

	bool IsFireRateValid() const;

	float GetCurrentFireRate() const;
	
	float GetTimeSinceLastFired() const;

private:
	double TimeLastFired = 0.0;
};