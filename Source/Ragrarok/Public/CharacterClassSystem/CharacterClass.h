// Copyright by Suspended Team.

#pragma once

#include "CoreMinimal.h"
#include "Characters/BaseCharacter.h"
#include "UObject/Object.h"
#include "CharacterClass.generated.h"

class ABaseCharacter;
class IAbilitySystemInterface;
class UAbilitySet;

UCLASS(Blueprintable)
class RAGRAROK_API UCharacterClass : public UObject
{
	GENERATED_BODY()
	
public:
	void OnClassChanged(ABaseCharacter* Character);

	UAbilitySet* GetAbilitySet() const { return AbilitySet; };
	
protected:
	UPROPERTY(EditDefaultsOnly, Category = "Abilities")
	TObjectPtr<UAbilitySet> AbilitySet;
	
	UPROPERTY(EditDefaultsOnly, Category = "Abilities")
	TSubclassOf<UPaperZDAnimInstance> AnimInstanceClass;
	
	UPROPERTY(EditDefaultsOnly, Category = "Abilities")
	TSubclassOf<UBaseWeaponInstance> CharacterWeaponClass;
};
