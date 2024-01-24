// Copyright by Suspended Team.


#include "Subsystems/SpriteEffectsManagerSubsystem.h"
#include "PaperFlipbookActor.h"
#include "PaperFlipbookComponent.h"
#include "PaperSpriteActor.h"
#include "PaperSpriteComponent.h"
#include "PaperFlipbook.h"

USpriteEffectsManagerSubsystem* USpriteEffectsManagerSubsystem::Get(const UObject* WorldContextObject)
{
	if (const UWorld* World = GEngine->GetWorldFromContextObject(WorldContextObject,
															 EGetWorldErrorMode::LogAndReturnNull))
	{
		USpriteEffectsManagerSubsystem* SpriteEffectsManagerSubsystem = World->GetSubsystem<USpriteEffectsManagerSubsystem>();
		return SpriteEffectsManagerSubsystem;
	}
	return nullptr;
}

void USpriteEffectsManagerSubsystem::SpawnSpriteEffectAtLocation(UPaperFlipbook* EffectFlipbook,
                                                                 const FTransform& SpawnTransform, AActor* Owner,
                                                                 AActor* ActorToAttach,
                                                                 FAttachmentTransformRules AttachmentTransformRules)
{
	APaperFlipbookActor* PaperFlipbookActor = GetWorld()->SpawnActorDeferred<APaperFlipbookActor>(
		APaperFlipbookActor::StaticClass(), FTransform::Identity, Owner);
	if (PaperFlipbookActor)
	{
		PaperFlipbookActor->GetRenderComponent()->SetFlipbook(EffectFlipbook);
		PaperFlipbookActor->SetLifeSpan(EffectFlipbook->GetTotalDuration());
		PaperFlipbookActor->FinishSpawning(SpawnTransform);
		if (ActorToAttach)
		{
			PaperFlipbookActor->AttachToActor(ActorToAttach, AttachmentTransformRules);
		}
	}
}

void USpriteEffectsManagerSubsystem::SpawnSpriteEffectAtLocation(UPaperSprite* EffectFlipbook,
	const FTransform& SpawnTransform, AActor* Owner, AActor* ActorToAttach,
	FAttachmentTransformRules AttachmentTransformRules,float SpriteLifeSpan)
{
	APaperSpriteActor* PaperSpriteActor = GetWorld()->SpawnActorDeferred<APaperSpriteActor>(
	APaperSpriteActor::StaticClass(), FTransform::Identity, Owner);
	if (PaperSpriteActor)
	{
		PaperSpriteActor->GetRenderComponent()->SetMobility(EComponentMobility::Movable);
		PaperSpriteActor->GetRenderComponent()->SetSprite(EffectFlipbook);
		PaperSpriteActor->SetActorEnableCollision(false);
		
		if (SpriteLifeSpan > 0)
		{
			PaperSpriteActor->SetLifeSpan(SpriteLifeSpan);
		}
		
		PaperSpriteActor->FinishSpawning(SpawnTransform);
		if (ActorToAttach)
		{
			PaperSpriteActor->AttachToActor(ActorToAttach, AttachmentTransformRules);
		}
	}
}
