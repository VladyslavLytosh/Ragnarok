// Copyright by Suspended Team.

#pragma once

#include "CoreMinimal.h"
#include "AbilitySystem/AbilitySystemInterface.h"
#include "PaperZDCharacter.h"
#include "BaseCharacter.generated.h"

class UCharacterClassComponent;
class UCharacterClass;
class UAbilitySet;
class URagnarokInputComponent;

UCLASS()
class RAGRAROK_API ABaseCharacter : public APaperZDCharacter, public IAbilitySystemInterface
{
	GENERATED_BODY()

public:
	ABaseCharacter();
	
	virtual UAbilitySystemComponent* GetAbilitySystemComponent() const override;

	virtual void SetupPlayerInputComponent(UInputComponent* PlayerInputComponent) override;

	virtual void BeginPlay() override;

	UCharacterClass* GetCurrentCharacterClass() const;
	
	const TArray<TSubclassOf<UCharacterClass>>& GetAvailableCharacterClasses() const;

	void SetCurrentCharacterClass(UCharacterClass* InCurrentCharacterClass);
	
protected:
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category="AbilitySystem")
	TObjectPtr<UAbilitySystemComponent> AbilitySystemComponent;
	
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category="Character Class")
	TObjectPtr<UCharacterClassComponent> CharacterClassComponent;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category="Input")
	TObjectPtr<URagnarokInputComponent> RagnarokInputComponent;

	UPROPERTY(EditDefaultsOnly, Category="AbilitySystem")
	TObjectPtr<UAbilitySet> DefaultAbilitySet;
};
