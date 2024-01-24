// Copyright by Suspended Team.


#include "Characters/DeathComponent.h"

#include "PaperFlipbook.h"
#include "PaperFlipbookComponent.h"
#include "PaperZDCharacter.h"
#include "Kismet/GameplayStatics.h"
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

	const APaperZDCharacter* OwnerCharacter = GetPawn<APaperZDCharacter>();
	if (OwnerCharacter && OwnerCharacter->GetSprite())
	{
		if (DeathData.DeathFlipbook)
		{
			USpriteEffectsManagerSubsystem* SpriteEffectsManagerSubsystem = GetWorld()->GetSubsystem<USpriteEffectsManagerSubsystem>();
			if (SpriteEffectsManagerSubsystem)
			{
				const int32 RandomFrame = FMath::RandRange(0, DeathData.DeathFlipbook->GetNumFrames() - 1);
				UPaperSprite* PaperSprite = DeathData.DeathFlipbook->GetSpriteAtFrame(RandomFrame);

				FTransform SpawnTransform = OwnerCharacter->GetSprite()->GetComponentTransform();
				SpawnTransform.SetLocation(SpawnTransform.GetLocation() + SpriteSpawnOffset);
				UE_LOG(LogTemp,Display,TEXT("Loc: %s"), *SpawnTransform.GetLocation().ToString())
				SpriteEffectsManagerSubsystem->SpawnSpriteEffectAtLocation(PaperSprite,SpawnTransform);
			}
		}
		if (BloodDecaClass)
		{
			AActor* DecalActor = GetWorld()->SpawnActor<AActor>(BloodDecaClass,OwnerCharacter->GetSprite()->GetComponentLocation(),OwnerCharacter->GetSprite()->GetComponentRotation());
			DecalActor->SetLifeSpan(DecalLifeSpan);
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
