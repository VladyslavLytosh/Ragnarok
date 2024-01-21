// Copyright by Suspended Team.


#include "Input/RagnarokInputComponent.h"
#include "EnhancedInputSubsystems.h"
#include "AbilitySystem/AbilitySystemComponent.h"
#include "AbilitySystem/AbilitySystemInterface.h"

void URagnarokInputComponent::InitializePlayerInput(UEnhancedInputComponent* PlayerInputComponent)
{
	if (!PlayerInputComponent || !InputConfig)
	{
		return;
	}
	
	const APawn* Pawn = GetPawn<APawn>();
	if (!Pawn) return;

	const APlayerController* PlayerController = Cast<APlayerController>(Pawn->GetController());
	if (!Pawn) return;

	UEnhancedInputLocalPlayerSubsystem* Subsystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(PlayerController->GetLocalPlayer());
	if (!Subsystem) return;

	Subsystem->ClearAllMappings();
	Subsystem->AddMappingContext(MappingContext, 0);

	TArray<uint32> BindHandles;
	BindAbilityActions(PlayerInputComponent,this, &ThisClass::Input_AbilityInputTagPressed, &ThisClass::Input_AbilityInputTagReleased, /*out*/ BindHandles);
}

void URagnarokInputComponent::Input_AbilityInputTagPressed(FGameplayTag InputTag)
{
	if (const IAbilitySystemInterface* AbilitySystemInterface = Cast<IAbilitySystemInterface>(GetPawn<APawn>()))
	{
		if (UAbilitySystemComponent* AbilitySystemComponent = AbilitySystemInterface->GetAbilitySystemComponent())
		{
			AbilitySystemComponent->AbilityInputTagPressed(InputTag);
		}
	}
}

void URagnarokInputComponent::Input_AbilityInputTagReleased(FGameplayTag InputTag)
{
	if (const IAbilitySystemInterface* AbilitySystemInterface = Cast<IAbilitySystemInterface>(GetPawn<APawn>()))
	{
		if (UAbilitySystemComponent* AbilitySystemComponent = AbilitySystemInterface->GetAbilitySystemComponent())
		{
			AbilitySystemComponent->AbilityInputTagReleased(InputTag);
		}
	}
}
