// Copyright by Suspended Team.

#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "ShieldBearerInterface.generated.h"

class UPaperFlipbookComponent;
class USphereComponent;

// This class does not need to be modified.
UINTERFACE(Blueprintable)
class UShieldBearerInterface : public UInterface
{
	GENERATED_BODY()
};

/**
 * 
 */
class RAGRAROK_API IShieldBearerInterface
{
	GENERATED_BODY()

	// Add interface functions to this class. This is the class that will be inherited to implement this interface.
public:
	virtual UPaperFlipbookComponent* GetShieldFlipbookComponent() const = 0;
};
