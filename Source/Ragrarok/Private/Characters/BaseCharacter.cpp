// Copyright by Suspended Team.

#include "Characters/BaseCharacter.h"

#include "PaperFlipbookComponent.h"
#include "AbilitySystem/AbilitySet.h"
#include "AbilitySystem/AbilitySystemComponent.h"
#include "Animations/RagnarokAnimInstance.h"
#include "CharacterClassSystem/CharacterClass.h"
#include "Characters/CharacterClassComponent.h"
#include "Characters/DeathComponent.h"
#include "Characters/HealthComponent.h"
#include "Components/BoxComponent.h"
#include "Data/CharacterDeathData.h"
#include "Engine/DamageEvents.h"
#include "Input/RagnarokInputComponent.h"
#include "Weapons/BaseWeaponInstance.h"

ABaseCharacter::ABaseCharacter()
{
	//PrimaryActorTick.bCanEverTick = true;

	AbilitySystemComponent = CreateDefaultSubobject<UAbilitySystemComponent>(TEXT("AbilitySystemComponent"));
	RagnarokInputComponent = CreateDefaultSubobject<URagnarokInputComponent>(TEXT("InputComponent"));
	CharacterClassComponent = CreateDefaultSubobject<UCharacterClassComponent>(TEXT("CharacterClassComponent"));
	HitBoxComponent = CreateDefaultSubobject<UBoxComponent>(TEXT("HitBoxComponent"));

	HitBoxComponent->SetupAttachment(GetSprite());
	DeathComponent = CreateDefaultSubobject<UDeathComponent>(TEXT("DeathComponent"));
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

URagnarokAnimInstance* ABaseCharacter::GetRagnarokAnimInstance() const
{
	return Cast<URagnarokAnimInstance>(GetAnimInstance());
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

float ABaseCharacter::TakeDamage(float DamageAmount, FDamageEvent const& DamageEvent, AController* EventInstigator,
	AActor* DamageCauser)
{
	const float SuperResult = Super::TakeDamage(DamageAmount, DamageEvent, EventInstigator, DamageCauser);
	
	UHealthComponent* HealthComponent = FindComponentByClass<UHealthComponent>();
	if (!HealthComponent)
	{
		return SuperResult;
	}
	
	UE_LOG(LogTemp,Warning,TEXT("Character: [%s] recive [%f] damage"), *GetName(),DamageAmount);

	HealthComponent->ReduceHealth(DamageAmount);
		
	if (HealthComponent->GetIsOutOfHealth())
	{
		const UCharacterClass* CurrentCharacterClass = GetCurrentCharacterClass();
		if (CurrentCharacterClass)
		{
			if (const UCharacterDeathData* CharacterDeathData = CurrentCharacterClass->GetCharacterDeathData())
			{
				DeathComponent->SetDeathData(CharacterDeathData->GetDeathDataByDamageType(DamageEvent.DamageTypeClass));
			}
		}
		DeathComponent->OnDeathStarted();
	}
	
	return SuperResult;
}
