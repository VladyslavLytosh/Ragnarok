// Copyright by Suspended Team.

#include "Characters/BaseCharacter.h"

#include "AbilitySystem/AbilitySet.h"
#include "AbilitySystem/AbilitySystemComponent.h"
#include "Input/RagnarokInputComponent.h"

ABaseCharacter::ABaseCharacter()
{
	//PrimaryActorTick.bCanEverTick = true;

	AbilitySystemComponent = CreateDefaultSubobject<UAbilitySystemComponent>(TEXT("AbilitySystemComponent"));
	RagnarokInputComponent = CreateDefaultSubobject<URagnarokInputComponent>(TEXT("InputComponent"));
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
	if (DefaultAbilitySetClass)
	{
		AbilitySystemComponent->GiveToAbilitySystem(DefaultAbilitySetClass.GetDefaultObject()->AbilitiesToGrant);
	}
}
