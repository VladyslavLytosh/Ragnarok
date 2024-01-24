// Copyright by Suspended Team.

#pragma once

#include "CoreMinimal.h"
#include "AbilitySystem/AbilitySystemInterface.h"
#include "PaperZDCharacter.h"
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
class RAGRAROK_API ABaseCharacter : public APaperZDCharacter, public IAbilitySystemInterface
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
	USphereComponent* GetShieldSphereComponent() const { return ShieldSphereComponent; }
	
	UFUNCTION(BlueprintPure)
	URagnarokAnimInstance* GetRagnarokAnimInstance() const;
	
	const TArray<TSubclassOf<UCharacterClass>>& GetAvailableCharacterClasses() const;

	void SetCurrentCharacterClass(UCharacterClass* InCurrentCharacterClass);
	
	void SetCurrentEquippedWeapon(TSubclassOf<UBaseWeaponInstance> CurrentEquippedWeaponClass);

	UBaseWeaponInstance* GetCurrentEquippedWeapon() const { return CurrentEquippedWeapon; }

	virtual float TakeDamage(float DamageAmount, FDamageEvent const& DamageEvent, AController* EventInstigator, AActor* DamageCauser) override;

protected:
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category="AbilitySystem")
	TObjectPtr<UAbilitySystemComponent> AbilitySystemComponent;
	
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category="Character Class")
	TObjectPtr<UCharacterClassComponent> CharacterClassComponent;

	UPROPERTY(EditDefaultsOnly,BlueprintReadOnly, Category="AbilitySystem")
	TObjectPtr<UAbilitySet> DefaultAbilitySet;
	
	UPROPERTY()
	TObjectPtr<UBaseWeaponInstance> CurrentEquippedWeapon;

	UPROPERTY(EditDefaultsOnly,BlueprintReadWrite, Category = "Components")
	TObjectPtr<UBoxComponent> HitBoxComponent;

	UPROPERTY(EditDefaultsOnly,BlueprintReadOnly, Category = "Components")
	TObjectPtr<UDeathComponent> DeathComponent;

	UPROPERTY(EditDefaultsOnly,BlueprintReadWrite, Category = "Components")
	TObjectPtr<USphereComponent> ShieldSphereComponent;
};
