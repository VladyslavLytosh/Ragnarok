// Copyright by Suspended Team.


#include "Characters/DeathComponent.h"
#include "AnimSequences/PaperZDAnimSequence.h"

UDeathComponent::UDeathComponent(const FObjectInitializer& ObjectInitializer) : Super(ObjectInitializer)
{
}

void UDeathComponent::OnDeathStarted()
{
	UE_LOG(LogTemp,Display,TEXT("Death Started"))
	if (GetWorld()->GetTimerManager().TimerExists(DeathTimerHandle) || bCharacterDead)
	{
		return;
	}
	
	bCharacterDead = true;
	if (DeathData.DeathAnimation)
	{
		GetWorld()->GetTimerManager().SetTimer(DeathTimerHandle,this,&ThisClass::FinishDeath,DeathData.DeathAnimation->GetTotalDuration());
	}
	
	if (OnCharacterDeathStarted.IsBound())
	{
		OnCharacterDeathStarted.Broadcast(GetPawn<APawn>());
	}
}

void UDeathComponent::SetDeathData(const FDeathData& NewDeathData)
{
	DeathData = NewDeathData;
}

void UDeathComponent::FinishDeath()
{
	if (OnCharacterDeathFinished.IsBound())
	{
		OnCharacterDeathFinished.Broadcast();
	}
}
