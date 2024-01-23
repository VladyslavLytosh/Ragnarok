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

	void AddHealth(const float& Amount);
	void ReduceHealth(const float& Amount);

#if WITH_EDITOR
	virtual void PostEditChangeProperty(FPropertyChangedEvent& PropertyChangedEvent) override;
#endif

private:
	UPROPERTY(EditDefaultsOnly,BlueprintReadOnly,Category="Health",meta=(AllowPrivateAccess=true,ClampMin=0.f,UIMin=0.f))
	float MaxHealth = 100.f;

	UPROPERTY(EditDefaultsOnly,BlueprintReadOnly,Category="Health",meta=(AllowPrivateAccess=true,ClampMin=0.f))
	float CurrentHealth;
};
