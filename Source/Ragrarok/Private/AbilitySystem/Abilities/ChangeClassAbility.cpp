// Copyright by Suspended Team.


#include "AbilitySystem/Abilities/ChangeClassAbility.h"
#include "CharacterClassSystem/CharacterClass.h"
#include "Characters/BaseCharacter.h"

void UChangeClassAbility::ActivateAbility(const FAbilityInfo& ActivationInfo)
{
	Super::ActivateAbility(ActivationInfo);
	
	ABaseCharacter* Character = Cast<ABaseCharacter>(ActivationInfo.AvatarPawn);
	if (!Character)
	{
		return;
	}

	const TArray<TSubclassOf<UCharacterClass>>& AvailableCharacterClasses = Character->GetAvailableCharacterClasses();
	if (NextClassIndex >= AvailableCharacterClasses.Num())
	{
		NextClassIndex = 0;
	}
	if (AvailableCharacterClasses.IsValidIndex(NextClassIndex))
	{
		if (UCharacterClass* CharacterClass = AvailableCharacterClasses[NextClassIndex].GetDefaultObject())
		{
			Character->SetCurrentCharacterClass(CharacterClass);
			++NextClassIndex;
		}
	}
	EndAbility();
}
