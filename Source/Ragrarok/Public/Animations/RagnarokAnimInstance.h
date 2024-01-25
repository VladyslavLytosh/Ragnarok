// Copyright by Suspended Team.

#pragma once

#include "CoreMinimal.h"
#include "PaperZDAnimInstance.h"
#include "RagnarokAnimInstance.generated.h"

class ABaseCharacter;
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
	
protected:
	virtual void OnInit_Implementation() override;
	
	virtual void Tick(float DeltaTime) override;
	
	UPROPERTY(BlueprintReadOnly, meta = (AllowPrivateAccess = true))
	TObjectPtr<ABaseCharacter> CachedCharacter;
	
	UPROPERTY(BlueprintReadOnly, meta = (AllowPrivateAccess = true))
	float CharacterVelocityLength;
};
