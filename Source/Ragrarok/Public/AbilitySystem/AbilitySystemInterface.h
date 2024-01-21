// Copyright by Suspended Team.

#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "AbilitySystemInterface.generated.h"

class UAbilitySystemComponent;
// This class does not need to be modified.
UINTERFACE(MinimalAPI)
class UAbilitySystemInterface : public UInterface
{
	GENERATED_BODY()
};

/**
 * 
 */
class RAGRAROK_API IAbilitySystemInterface
{
	GENERATED_BODY()

	// Add interface functions to this class. This is the class that will be inherited to implement this interface.
public:
	virtual UAbilitySystemComponent* GetAbilitySystemComponent() const = 0;
};
