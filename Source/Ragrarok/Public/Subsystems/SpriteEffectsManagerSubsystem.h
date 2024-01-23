// Copyright by Suspended Team.

#pragma once

#include "CoreMinimal.h"
#include "Subsystems/WorldSubsystem.h"
#include "SpriteEffectsManagerSubsystem.generated.h"

class UPaperFlipbook;

UCLASS()
class RAGRAROK_API USpriteEffectsManagerSubsystem : public UWorldSubsystem
{
	GENERATED_BODY()

public:
	static USpriteEffectsManagerSubsystem* Get(const UObject* WorldContextObject);

	void SpawnSpriteEffectAtLocation(UPaperFlipbook* EffectFlipbook, const FTransform& SpawnTransform,
	                                 AActor* Owner = nullptr,
	                                 AActor* ActorToAttach = nullptr,
	                                 FAttachmentTransformRules AttachmentTransformRules =
		                                 FAttachmentTransformRules::KeepWorldTransform);
};