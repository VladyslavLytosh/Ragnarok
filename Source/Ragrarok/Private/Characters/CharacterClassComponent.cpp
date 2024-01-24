// Copyright by Suspended Team.


#include "Characters/CharacterClassComponent.h"

#include "CharacterClassSystem/CharacterClass.h"
#include "PaperFlipbookActor.h"
#include "PaperFlipbookComponent.h"
#include "PaperFlipbook.h"
#include "AbilitySystem/AbilitySet.h"
#include "AbilitySystem/AbilitySystemComponent.h"
#include "Subsystems/SpriteEffectsManagerSubsystem.h"

UCharacterClassComponent::UCharacterClassComponent(const FObjectInitializer& ObjectInitializer)
: Super(ObjectInitializer)
{
	PrimaryComponentTick.bCanEverTick = false;
}

void UCharacterClassComponent::BeginPlay()
{
	Super::BeginPlay();
	if (!AvailableCharacterClasses.IsEmpty())
	{
		CurrentCharacterClass = AvailableCharacterClasses[0].GetDefaultObject();
		if (CurrentCharacterClass)
		{
			CurrentCharacterClass->OnClassChanged(Cast<ABaseCharacter>(GetOwner()));
		}
	}
}
 
void UCharacterClassComponent::SetCurrentCharacterClass(UCharacterClass* InCurrentCharacterClass, ABaseCharacter* Character)
{
	if (InCurrentCharacterClass)
	{
		RemovePreviousClassAbilities(Character);
		CurrentCharacterClass = InCurrentCharacterClass;
		CurrentCharacterClass->OnClassChanged(Character);
		
		if (USpriteEffectsManagerSubsystem* SpriteEffectsManagerSubsystem = USpriteEffectsManagerSubsystem::Get(this))
		{
			FTransform SpawnTransform;
			SpawnTransform.SetLocation(GetOwner()->GetActorLocation());
			SpawnTransform.SetRotation(FRotator(0, 0, -90).Quaternion());
			SpawnTransform.SetScale3D(EffectScale);
			SpriteEffectsManagerSubsystem->SpawnSpriteEffectAtLocation(ChangeClassEffectFlipbook,
			                                                           SpawnTransform, GetOwner(), GetOwner(),
			                                                           FAttachmentTransformRules::KeepWorldTransform,
			                                                           ChangeClassEffectFlipbook->GetTotalDuration());
		}
	}
}

void UCharacterClassComponent::RemovePreviousClassAbilities(const ABaseCharacter* Character)
{
	UAbilitySystemComponent* AbilitySystemComponent = Character->GetAbilitySystemComponent();
	if (CurrentCharacterClass)
	{
		if (const UAbilitySet* AbilitySet = CurrentCharacterClass->GetAbilitySet())
		{
			AbilitySystemComponent->TakeFromAbilitySystem(AbilitySet->AbilitiesToGrant);
		}
	}
}
