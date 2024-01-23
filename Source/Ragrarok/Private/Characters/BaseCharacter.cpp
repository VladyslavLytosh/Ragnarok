// Copyright by Suspended Team.

#include "Characters/BaseCharacter.h"

#include "PaperFlipbookComponent.h"
#include "AbilitySystem/AbilitySet.h"
#include "AbilitySystem/AbilitySystemComponent.h"
#include "Animations/RagnarokAnimInstance.h"
#include "Characters/CharacterClassComponent.h"
#include "Characters/HealthComponent.h"
#include "Components/BoxComponent.h"
#include "Input/RagnarokInputComponent.h"

ABaseCharacter::ABaseCharacter()
{
	//PrimaryActorTick.bCanEverTick = true;

	AbilitySystemComponent = CreateDefaultSubobject<UAbilitySystemComponent>(TEXT("AbilitySystemComponent"));
	RagnarokInputComponent = CreateDefaultSubobject<URagnarokInputComponent>(TEXT("InputComponent"));
	CharacterClassComponent = CreateDefaultSubobject<UCharacterClassComponent>(TEXT("CharacterClassComponent"));
	HitBoxComponent = CreateDefaultSubobject<UBoxComponent>(TEXT("HitBoxComponent"));

	HitBoxComponent->SetupAttachment(GetSprite());
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

float ABaseCharacter::TakeDamage(float DamageAmount, FDamageEvent const& DamageEvent, AController* EventInstigator,
	AActor* DamageCauser)
{
	if (UHealthComponent* HealthComponent = FindComponentByClass<UHealthComponent>())
	{
		UE_LOG(LogTemp,Warning,TEXT("Character: [%s] recive [%f] damage"), *GetName(),DamageAmount);
		HealthComponent->ReduceHealth(DamageAmount);
	}
	return Super::TakeDamage(DamageAmount, DamageEvent, EventInstigator, DamageCauser);
}
