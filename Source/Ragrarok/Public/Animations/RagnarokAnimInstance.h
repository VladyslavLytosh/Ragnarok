// Copyright by Suspended Team.

#pragma once

#include "CoreMinimal.h"
#include "PaperZDAnimInstance.h"
#include "RagnarokAnimInstance.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE(FAttackNotifyDelegate);

/**
 * Ragnarok paperZD anim instance class
 */
UCLASS(Blueprintable,Blueprintable)
class RAGRAROK_API URagnarokAnimInstance : public UPaperZDAnimInstance
{
	GENERATED_BODY()
public:
	FAttackNotifyDelegate AttackNotifyDelegate;
};
