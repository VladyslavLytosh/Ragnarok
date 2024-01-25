// Copyright by Suspended Team.

#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "WeaponHolderInterface.generated.h"

class UBaseWeaponInstance;

// This class does not need to be modified.
UINTERFACE(Blueprintable)
class UWeaponHolderInterface : public UInterface
{
	GENERATED_BODY()
};

/**
 * 
 */
class RAGRAROK_API IWeaponHolderInterface
{
	GENERATED_BODY()

	// Add interface functions to this class. This is the class that will be inherited to implement this interface.
public:
	virtual UBaseWeaponInstance* GetCurrentEquippedWeapon() const = 0;

	virtual void SetCurrentEquippedWeapon(TSubclassOf<UBaseWeaponInstance> CurrentEquippedWeaponClass) = 0;
};
