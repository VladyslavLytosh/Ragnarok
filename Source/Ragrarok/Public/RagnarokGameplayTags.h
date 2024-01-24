// Copyright by Suspended Team.

#pragma once

#include "GameplayTagContainer.h"

struct FRagnarokGameplayTags : public FGameplayTagNativeAdder
{
	virtual ~FRagnarokGameplayTags(){}
	
	static const FRagnarokGameplayTags& Get() { return GameplayTags; }
	
	static FGameplayTag FindTagByString(FString TagString, bool bMatchPartialString = false);
	/*InputTags*/
	FGameplayTag InputTag_Ability_ChangeClass;
	FGameplayTag InputTag_Ability_Dash;
	FGameplayTag InputTag_Ability_Melee;
	FGameplayTag InputTag_Ability_Fire;
	FGameplayTag InputTag_Ability_Shield;
	FGameplayTag Ability_ShieldActive;

protected:
	virtual void AddTags() override;
	
	void AddTag(FGameplayTag& OutTag, const ANSICHAR* TagName, const ANSICHAR* TagComment);

private:
	static FRagnarokGameplayTags GameplayTags;
};
