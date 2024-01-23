// Copyright by Suspended Team.

#pragma once

#include "CoreMinimal.h"
#include "AbilitySystem/AbilitySystemInterface.h"
#include "PaperZDCharacter.h"
#include "BaseCharacter.generated.h"

class URagnarokAnimInstance;
class UBoxComponent;
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
	
	UFUNCTION(BlueprintPure)
	UCharacterClass* GetCurrentCharacterClass() const;
	UFUNCTION(BlueprintPure)
	UBoxComponent* GetHitBoxComponent() const {return HitBoxComponent;}
	UFUNCTION(BlueprintPure)
	URagnarokAnimInstance* GetRagnarokAnimInstance() const;
	
	const TArray<TSubclassOf<UCharacterClass>>& GetAvailableCharacterClasses() const;

	void SetCurrentCharacterClass(UCharacterClass* InCurrentCharacterClass);

	virtual float TakeDamage(float DamageAmount, FDamageEvent const& DamageEvent, AController* EventInstigator, AActor* DamageCauser) override;
protected:
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category="AbilitySystem")
	TObjectPtr<UAbilitySystemComponent> AbilitySystemComponent;
	
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category="Character Class")
	TObjectPtr<UCharacterClassComponent> CharacterClassComponent;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category="Input")
	TObjectPtr<URagnarokInputComponent> RagnarokInputComponent;

	UPROPERTY(EditDefaultsOnly,BlueprintReadOnly, Category="AbilitySystem")
	TObjectPtr<UAbilitySet> DefaultAbilitySet;

	UPROPERTY(EditDefaultsOnly,BlueprintReadWrite, Category = "HitBox")
	TObjectPtr<UBoxComponent> HitBoxComponent;
};
