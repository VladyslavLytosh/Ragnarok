// Copyright by Suspended Team.

#pragma once

#include "CoreMinimal.h"
#include "Subsystems/WorldSubsystem.h"
#include "SpriteEffectsManagerSubsystem.generated.h"

class UPaperSprite;
class UPaperFlipbook;

UCLASS()
class RAGRAROK_API USpriteEffectsManagerSubsystem : public UWorldSubsystem
{
	GENERATED_BODY()

public:
	UFUNCTION(BlueprintCallable)
	static USpriteEffectsManagerSubsystem* Get(const UObject* WorldContextObject);

	void SpawnSpriteEffectAtLocation(UPaperFlipbook* EffectFlipbook, const FTransform& SpawnTransform,
	                                 AActor* Owner = nullptr,
	                                 AActor* ActorToAttach = nullptr,
	                                 FAttachmentTransformRules AttachmentTransformRules =
		                                 FAttachmentTransformRules::KeepWorldTransform,
		                                 float FlipbookLifeSpan = -1.f);
	
	void SpawnSpriteEffectAtLocation(UPaperSprite* EffectSprite, const FTransform& SpawnTransform,
									 AActor* Owner = nullptr,
									 AActor* ActorToAttach = nullptr,
									 FAttachmentTransformRules AttachmentTransformRules =
										 FAttachmentTransformRules::KeepWorldTransform,
										 float SpriteLifeSpawn = -1.f);
};