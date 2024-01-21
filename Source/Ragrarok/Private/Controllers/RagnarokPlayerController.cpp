// Copyright by Suspended Team.


#include "Controllers/RagnarokPlayerController.h"
#include "Characters/BaseCharacter.h"
#include "AbilitySystem/AbilitySystemComponent.h"
#include "AbilitySystem/AbilitySystemInterface.h"

void ARagnarokPlayerController::ProcessPlayerInput(const float DeltaTime, const bool bGamePaused)
{
	Super::ProcessPlayerInput(DeltaTime, bGamePaused);

	if (const IAbilitySystemInterface* AbilitySystemInterface = Cast<IAbilitySystemInterface>(GetCharacter()))
	{
		if (UAbilitySystemComponent* AbilitySystemComponent = AbilitySystemInterface->GetAbilitySystemComponent())
		{
			AbilitySystemComponent->ProcessAbilityInput(DeltaTime,bGamePaused);
		}
	}
}
