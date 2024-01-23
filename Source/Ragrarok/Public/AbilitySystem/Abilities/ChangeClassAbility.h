// Copyright by Suspended Team.

#pragma once

#include "CoreMinimal.h"
#include "AbilitySystem/AbilityBase.h"
#include "ChangeClassAbility.generated.h"

UCLASS()
class RAGRAROK_API UChangeClassAbility : public UAbilityBase
{
	GENERATED_BODY()

protected:
	virtual void ActivateAbility(const FAbilityInfo& ActivationInfo) override;

private:
	int32 NextClassIndex = 1;
};
