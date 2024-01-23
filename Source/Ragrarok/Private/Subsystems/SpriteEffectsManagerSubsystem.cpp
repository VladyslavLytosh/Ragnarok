﻿// Copyright by Suspended Team.


#include "Subsystems/SpriteEffectsManagerSubsystem.h"
#include "PaperFlipbookActor.h"
#include "PaperFlipbookComponent.h"
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