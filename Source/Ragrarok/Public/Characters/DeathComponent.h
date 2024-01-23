// Copyright by Suspended Team.

#pragma once

#include "CoreMinimal.h"
#include "Components/PawnComponent.h"
#include "DeathComponent.generated.h"

class UPaperZDAnimSequence;

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FDeathStartedDelegate, APawn*, OwnerPawn);
DECLARE_DYNAMIC_MULTICAST_DELEGATE(FDeathFinishedDelegate);

UCLASS(ClassGroup=(Custom), meta=(BlueprintSpawnableComponent))
class RAGRAROK_API UDeathComponent : public UPawnComponent
{
	GENERATED_BODY()

public:
	UDeathComponent(const FObjectInitializer& ObjectInitializer = FObjectInitializer::Get());

	void OnDeathStarted();
	
	void SetDeathAnimation(UPaperZDAnimSequence* DeathAnim);

	bool IsCharacterDead() const {return bCharacterDead;}

	UPROPERTY(BlueprintAssignable)
	FDeathStartedDelegate OnCharacterDeathStarted;
	UPROPERTY(BlueprintAssignable)
	FDeathFinishedDelegate OnCharacterDeathFinished;
	
protected:
	void FinishDeath();

	UPROPERTY(VisibleDefaultsOnly,Category="Animations")
	UPaperZDAnimSequence* DeathAnimation;

	UPROPERTY()
	bool bCharacterDead = false;

	UPROPERTY()
	FTimerHandle DeathTimerHandle;
};
