// Copyright by Suspended Team.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "RagnarokPlayerController.generated.h"

/**
 * Ragnarok PlayerController class
 */
UCLASS()
class RAGRAROK_API ARagnarokPlayerController : public APlayerController
{
	GENERATED_BODY()
	
protected:
	virtual void ProcessPlayerInput(const float DeltaTime, const bool bGamePaused) override;
};
