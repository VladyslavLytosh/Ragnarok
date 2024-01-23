// Copyright by Suspended Team.

#include "Characters/BaseCharacter.h"

#include "AbilitySystem/AbilitySet.h"
#include "AbilitySystem/AbilitySystemComponent.h"
#include "Characters/CharacterClassComponent.h"
#include "Input/RagnarokInputComponent.h"
#include "Weapons/BaseWeaponInstance.h"

ABaseCharacter::ABaseCharacter()
{
	//PrimaryActorTick.bCanEverTick = true;

	AbilitySystemComponent = CreateDefaultSubobject<UAbilitySystemComponent>(TEXT("AbilitySystemComponent"));
	RagnarokInputComponent = CreateDefaultSubobject<URagnarokInputComponent>(TEXT("InputComponent"));
	CharacterClassComponent = CreateDefaultSubobject<UCharacterClassComponent>(TEXT("CharacterClassComponent"));
}

UAbilitySystemComponent* ABaseCharacter::GetAbilitySystemComponent() const
{
	return AbilitySystemComponent;
}

void ABaseCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);
	check(RagnarokInputComponent);

	UEnhancedInputComponent* EnhancedInputComponent = Cast<UEnhancedInputComponent>(InputComponent);
	check(EnhancedInputComponent);
	
	RagnarokInputComponent->InitializePlayerInput(EnhancedInputComponent);
}

void ABaseCharacter::BeginPlay()
{
	Super::BeginPlay();
	
	if (DefaultAbilitySet)
	{
		AbilitySystemComponent->GiveToAbilitySystem(DefaultAbilitySet->AbilitiesToGrant);
	}
}

UCharacterClass* ABaseCharacter::GetCurrentCharacterClass() const
{
	return CharacterClassComponent->GetCurrentCharacterClass();
}

const TArray<TSubclassOf<UCharacterClass>>& ABaseCharacter::GetAvailableCharacterClasses() const
{
	return CharacterClassComponent->GetAvailableCharacterClasses();
}

void ABaseCharacter::SetCurrentCharacterClass(UCharacterClass* InCurrentCharacterClass)
{
	CharacterClassComponent->SetCurrentCharacterClass(InCurrentCharacterClass, this);
}

void ABaseCharacter::SetCurrentEquippedWeapon(TSubclassOf<UBaseWeaponInstance> CurrentEquippedWeaponClass)
{
	CurrentEquippedWeapon = NewObject<UBaseWeaponInstance>(this, CurrentEquippedWeaponClass);
}
