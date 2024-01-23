// Copyright by Suspended Team.


#include "Characters/DeathComponent.h"
#include "AnimSequences/PaperZDAnimSequence.h"

UDeathComponent::UDeathComponent(const FObjectInitializer& ObjectInitializer) : Super(ObjectInitializer)
{
}

void UDeathComponent::OnDeathStarted()
{
	if (GetWorld()->GetTimerManager().TimerExists(DeathTimerHandle) || bCharacterDead)
	{
		return;
	}
	
	bCharacterDead = true;
	if (DeathAnimation)
	{
		GetWorld()->GetTimerManager().SetTimer(DeathTimerHandle,this,&ThisClass::FinishDeath,DeathAnimation->GetTotalDuration());
	}
	
	if (OnCharacterDeathStarted.IsBound())
	{
		OnCharacterDeathStarted.Broadcast(GetPawn<APawn>());
	}
}

void UDeathComponent::SetDeathAnimation(UPaperZDAnimSequence* DeathAnim)
{
	DeathAnimation = DeathAnim;
}

void UDeathComponent::FinishDeath()
{
	if (OnCharacterDeathFinished.IsBound())
	{
		OnCharacterDeathFinished.Broadcast();
	}
}
