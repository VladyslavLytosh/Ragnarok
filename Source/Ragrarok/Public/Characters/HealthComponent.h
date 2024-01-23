// Copyright by Suspended Team.

#pragma once

#include "CoreMinimal.h"
#include "Components/PawnComponent.h"
#include "HealthComponent.generated.h"


UCLASS(ClassGroup=(Custom), meta=(BlueprintSpawnableComponent))
class RAGRAROK_API UHealthComponent : public UPawnComponent
{
	GENERATED_BODY()

public:
	UHealthComponent(const FObjectInitializer& ObjectInitializer = FObjectInitializer::Get());
};
