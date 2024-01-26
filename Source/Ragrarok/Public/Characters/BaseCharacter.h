// Copyright by Suspended Team.

#pragma once

#include "CoreMinimal.h"
#include "AbilitySystem/AbilitySystemInterface.h"
#include "PaperZDCharacter.h"
#include "Interfaces/WeaponHolderInterface.h"
#include "BaseCharacter.generated.h"

class USphereComponent;
class UDeathComponent;
class UBaseWeaponInstance;
class URagnarokAnimInstance;
class UBoxComponent;
class UCharacterClassComponent;
class UCharacterClass;
class UAbilitySet;
class URagnarokInputComponent;

UCLASS()
class RAGRAROK_API ABaseCharacter : public APaperZDCharacter, public IAbilitySystemInterface, public IWeaponHolderInterface
{
	GENERATED_BODY()

public:
	ABaseCharacter();
	
	virtual UAbilitySystemComponent* GetAbilitySystemComponent() const override;
	
	virtual void BeginPlay() override;
	
	UFUNCTION(BlueprintPure)
	UCharacterClass* GetCurrentCharacterClass() const;
	
	UFUNCTION(BlueprintPure)
	UBoxComponent* GetHitBoxComponent() const { return HitBoxComponent; }

	UFUNCTION(BlueprintPure)
	virtual UBaseWeaponInstance* GetCurrentEquippedWeapon() const override { return CurrentEquippedWeapon; }

	UFUNCTION(BlueprintCallable)
	virtual void SetCurrentEquippedWeapon(TSubclassOf<UBaseWeaponInstance> CurrentEquippedWeaponClass) override;
	
	UFUNCTION(BlueprintPure)
	URagnarokAnimInstance* GetRagnarokAnimInstance() const;
	
	const TArray<TSubclassOf<UCharacterClass>>& GetAvailableCharacterClasses() const;

	void SetCurrentCharacterClass(UCharacterClass* InCurrentCharacterClass);
	
	virtual float TakeDamage(float DamageAmount, FDamageEvent const& DamageEvent, AController* EventInstigator, AActor* DamageCauser) override;

protected:
	UPROPERTY()
	TObjectPtr<UBaseWeaponInstance> CurrentEquippedWeapon;
	
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category="AbilitySystem")
	TObjectPtr<UAbilitySystemComponent> AbilitySystemComponent;
	
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category="Character Class")
	TObjectPtr<UCharacterClassComponent> CharacterClassComponent;

	UPROPERTY(EditDefaultsOnly,BlueprintReadOnly, Category="AbilitySystem")
	TObjectPtr<UAbilitySet> DefaultAbilitySet;

	UPROPERTY(EditDefaultsOnly,BlueprintReadOnly, Category = "Components")
	TObjectPtr<UDeathComponent> DeathComponent;

	UPROPERTY(EditDefaultsOnly,BlueprintReadWrite, Category = "Components")
	TObjectPtr<UBoxComponent> HitBoxComponent;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly,Category="Damage")
	TObjectPtr<USoundBase> HurtSound;
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly,Category="Damage")
	TObjectPtr<USoundBase> DeathSound;
};
