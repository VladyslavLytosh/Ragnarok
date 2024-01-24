﻿// Copyright by Suspended Team.


#include "RagnarokGameplayTags.h"

#include "GameplayTagsManager.h"

FRagnarokGameplayTags FRagnarokGameplayTags::GameplayTags;

void FRagnarokGameplayTags::AddTags()
{
	AddTag(InputTag_Ability_ChangeClass, "InputTag.Ability.ChangeClass", "Change Class input.");
	AddTag(InputTag_Ability_Dash, "InputTag.Ability.Dash", "Dash ability input.");
	AddTag(InputTag_Ability_Melee, "InputTag.Ability.Melee", "Melee ability input.");
	AddTag(InputTag_Ability_Fire, "InputTag.Ability.Fire", "Fire ability input.");
	AddTag(InputTag_Ability_Shield, "InputTag.Ability.Shield", "Shield ability input.");
	AddTag(Ability_ShieldActive, "Ability.Shield", "Shield active tag.");
}

void FRagnarokGameplayTags::AddTag(FGameplayTag& OutTag, const ANSICHAR* TagName, const ANSICHAR* TagComment)
{
	OutTag = UGameplayTagsManager::Get().AddNativeGameplayTag(FName(TagName), FString(TEXT("(Native) ")) + FString(TagComment));
}

FGameplayTag FRagnarokGameplayTags::FindTagByString(FString TagString, bool bMatchPartialString)
{
	const UGameplayTagsManager& Manager = UGameplayTagsManager::Get();
	FGameplayTag Tag = Manager.RequestGameplayTag(FName(*TagString), false);

	if (!Tag.IsValid() && bMatchPartialString)
	{
		FGameplayTagContainer AllTags;
		Manager.RequestAllGameplayTags(AllTags, true);

		for (const FGameplayTag TestTag : AllTags)
		{
			if (TestTag.ToString().Contains(TagString))
			{
				UE_LOG(LogTemp, Display, TEXT("Could not find exact match for tag [%s] but found partial match on tag [%s]."), *TagString, *TestTag.ToString());
				Tag = TestTag;
				break;
			}
		}
	}
	return Tag;
}