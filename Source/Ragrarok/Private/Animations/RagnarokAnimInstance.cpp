// Copyright by Suspended Team.


#include "Animations/RagnarokAnimInstance.h"

#include "Characters/BaseCharacter.h"

void URagnarokAnimInstance::OnInit_Implementation()
{
	Super::OnInit_Implementation();

	if (ABaseCharacter* Character = Cast<ABaseCharacter>(GetOwningActor()))
	{
		CachedCharacter = Character;
	}
}

void URagnarokAnimInstance::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if (CachedCharacter)
	{
		CharacterVelocityLength = CachedCharacter->GetVelocity().Length();
	}
}
