﻿// Copyright by Suspended Team.


#include "Characters/DeathComponent.h"

#include "PaperFlipbook.h"
#include "PaperFlipbookComponent.h"
#include "PaperZDCharacter.h"
#include "Subsystems/SpriteEffectsManagerSubsystem.h"

UDeathComponent::UDeathComponent(const FObjectInitializer& ObjectInitializer) : Super(ObjectInitializer)
{
}

void UDeathComponent::OnDeathStarted()
{
	UE_LOG(LogTemp,Display,TEXT("Death Started"))
	if (bCharacterDead)
	{
		return;
	}
	
	bCharacterDead = true;
	if (OnCharacterDeathStarted.IsBound())
	{
		OnCharacterDeathStarted.Broadcast(GetPawn<APawn>());
	}

	if (DeathData.DeathFlipbook)
	{
		APaperZDCharacter* OwnerCharacter = GetPawn<APaperZDCharacter>();
		USpriteEffectsManagerSubsystem* SpriteEffectsManagerSubsystem = GetWorld()->GetSubsystem<USpriteEffectsManagerSubsystem>();
		if (SpriteEffectsManagerSubsystem && OwnerCharacter && OwnerCharacter->GetSprite())
		{
			const int32 RandomFrame = FMath::RandRange(0, DeathData.DeathFlipbook->GetNumFrames());
			UPaperSprite* PaperSprite = DeathData.DeathFlipbook->GetSpriteAtFrame(RandomFrame);

			FTransform SpawnTransform = OwnerCharacter->GetSprite()->GetComponentTransform();
			SpawnTransform.SetLocation(SpawnTransform.GetLocation() + FVector::DownVector * 10);
			SpriteEffectsManagerSubsystem->SpawnSpriteEffectAtLocation(PaperSprite,OwnerCharacter->GetSprite()->GetComponentTransform());
		}
	}

	FinishDeath();
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
		OnCharacterDeathFinished.RemoveAll(this);
	}

	check(GetOwner());
	GetOwner()->Destroy();
}