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
#include "Kismet/GameplayStatics.h"
#include "Weapons/BaseWeaponInstance.h"

ABaseCharacter::ABaseCharacter()
{
	//PrimaryActorTick.bCanEverTick = true;

	AbilitySystemComponent = CreateDefaultSubobject<UAbilitySystemComponent>(TEXT("AbilitySystemComponent"));
	CharacterClassComponent = CreateDefaultSubobject<UCharacterClassComponent>(TEXT("CharacterClassComponent"));
	HitBoxComponent = CreateDefaultSubobject<UBoxComponent>(TEXT("HitBoxComponent"));
	
	HitBoxComponent->SetupAttachment(GetSprite());
	
	DeathComponent = CreateDefaultSubobject<UDeathComponent>(TEXT("DeathComponent"));
}

UAbilitySystemComponent* ABaseCharacter::GetAbilitySystemComponent() const
{
	return AbilitySystemComponent;
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

void ABaseCharacter::SetCurrentEquippedWeapon(TSubclassOf<UBaseWeaponInstance> CurrentEquippedWeaponClass)
{
	CurrentEquippedWeapon = NewObject<UBaseWeaponInstance>(this, CurrentEquippedWeaponClass);
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

float ABaseCharacter::TakeDamage(float DamageAmount, FDamageEvent const& DamageEvent, AController* EventInstigator,
	AActor* DamageCauser)
{
	if (!bReceiveDamage)
	{
		return 0;
	}
	
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
		UGameplayStatics::PlaySoundAtLocation(GetWorld(),DeathSound,GetActorLocation(),GetActorRotation());
		DeathComponent->OnDeathStarted();
	}
	else
	{
		UGameplayStatics::PlaySoundAtLocation(GetWorld(),HurtSound,GetActorLocation(),GetActorRotation());
	}
	
	return SuperResult;
}
