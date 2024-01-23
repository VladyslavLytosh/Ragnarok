// Copyright by Suspended Team.

#pragma once

#include "CoreMinimal.h"
#include "Notifies/PaperZDAnimNotify.h"
#include "AttackAnimNotify.generated.h"

/**
 * Custom attack anim notify class
 */
UCLASS(Blueprintable,Blueprintable)
class RAGRAROK_API UAttackAnimNotify : public UPaperZDAnimNotify
{
	GENERATED_BODY()

public:
	virtual void OnReceiveNotify_Implementation(UPaperZDAnimInstance* OwningInstance) override;
};
