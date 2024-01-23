// Copyright by Suspended Team.


#include "Characters/CharacterClassComponent.h"

#include "CharacterClassSystem/CharacterClass.h"
#include "PaperFlipbookActor.h"
#include "PaperFlipbookComponent.h"
#include "PaperFlipbook.h"
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
 
void UCharacterClassComponent::SetCurrentCharacterClass(UCharacterClass* InCurrentCharacterClass, const ABaseCharacter* Character)
{
	if (InCurrentCharacterClass)
	{
		CurrentCharacterClass = InCurrentCharacterClass;
		CurrentCharacterClass->OnClassChanged(Character);

		if (USpriteEffectsManagerSubsystem* SpriteEffectsManagerSubsystem = USpriteEffectsManagerSubsystem::Get(this))
		{
			FTransform SpawnTransform;
			SpawnTransform.SetLocation(GetOwner()->GetActorLocation());
			SpawnTransform.SetRotation(FRotator(0, 0, -90).Quaternion());
			SpawnTransform.SetScale3D(EffectScale);
			SpriteEffectsManagerSubsystem->SpawnSpriteEffectAtLocation(ChangeClassEffectFlipbook,
			                                                           SpawnTransform, GetOwner(), GetOwner());
		}
	}
}
