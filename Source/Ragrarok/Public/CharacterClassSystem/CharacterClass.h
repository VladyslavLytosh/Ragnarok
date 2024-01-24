// Copyright by Suspended Team.

#pragma once

#include "CoreMinimal.h"
#include "Characters/BaseCharacter.h"
#include "UObject/Object.h"
#include "CharacterClass.generated.h"

class UCharacterDeathData;
class ABaseCharacter;
class IAbilitySystemInterface;
class UAbilitySet;

UCLASS(Blueprintable)
class RAGRAROK_API UCharacterClass : public UObject
{
	GENERATED_BODY()
	
public:
	void OnClassChanged(ABaseCharacter* Character);

	UFUNCTION(BlueprintPure)
	UAbilitySet* GetAbilitySet() const { return AbilitySet; };

	UFUNCTION(BlueprintPure)
	UCharacterDeathData* GetCharacterDeathData() const {return CharacterDeathData;}

	UFUNCTION(BlueprintPure)
	TSubclassOf<UBaseWeaponInstance> GetCharacterWeaponClass() const {return CharacterWeaponClass;}
	
protected:
	UPROPERTY(EditDefaultsOnly, Category = "Abilities")
	TObjectPtr<UAbilitySet> AbilitySet;
	
	UPROPERTY(EditDefaultsOnly, Category = "Abilities")
	TSubclassOf<UPaperZDAnimInstance> AnimInstanceClass;
	
	UPROPERTY(EditDefaultsOnly, Category = "Abilities")
	TSubclassOf<UBaseWeaponInstance> CharacterWeaponClass;

	UPROPERTY(EditDefaultsOnly,Category="Death")
	TObjectPtr<UCharacterDeathData> CharacterDeathData;
};
