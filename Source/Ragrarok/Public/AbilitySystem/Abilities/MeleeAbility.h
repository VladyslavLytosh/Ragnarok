// Copyright by Suspended Team.

#pragma once

#include "CoreMinimal.h"
#include "AbilitySystem/AbilityBase.h"
#include "Characters/BaseCharacter.h"
#include "MeleeAbility.generated.h"

class ABaseCharacter;
class UPaperZDAnimSequence;

/**
 * Melee Ability class
 */
UCLASS()
class RAGRAROK_API UMeleeAbility : public UAbilityBase
{
	GENERATED_BODY()

protected:
	virtual void ActivateAbility(const FAbilityInfo& ActivationInfo) override;
	virtual void EndAbility() override;
	
	void ApplyMeleeAttackToTarget(ABaseCharacter* InstigatorCharacter, ABaseCharacter* TargetCharacter);

	UFUNCTION()
	void CheckHit();
	
	UPROPERTY(EditDefaultsOnly,Category="Animations")
	UPaperZDAnimSequence* MeleeAttackAnimation;
	
	UPROPERTY(EditDefaultsOnly)
	TSubclassOf<ABaseCharacter> CharacterClass;
	UPROPERTY(EditDefaultsOnly)
	TSubclassOf<UDamageType> DamageType;
	
	UPROPERTY(EditDefaultsOnly)
	float DamageAmount;

	UPROPERTY()
	FTimerHandle EndAnimationTimerHandle;
};
