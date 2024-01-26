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

	UFUNCTION(BlueprintCallable)
	void AddHealth(const float& Amount);
	UFUNCTION(BlueprintCallable)
	void ReduceHealth(const float& Amount);

	UFUNCTION(BlueprintPure)
	bool GetIsOutOfHealth() const {return bOutOfHealth;}
	
#if WITH_EDITOR
	virtual void PostEditChangeProperty(FPropertyChangedEvent& PropertyChangedEvent) override;
#endif

private:
	void SetHealth(const float NewHealth);
	
	UPROPERTY(EditDefaultsOnly,BlueprintReadOnly,Category="Health",meta=(AllowPrivateAccess=true,ClampMin=0.f,UIMin=0.f))
	float MaxHealth = 100.f;

	UPROPERTY(VisibleAnywhere,BlueprintReadOnly,Category="Health",meta=(AllowPrivateAccess=true,ClampMin=0.f))
	float CurrentHealth;

	UPROPERTY(BlueprintReadOnly, VisibleAnywhere, meta=(AllowPrivateAccess=true))
	bool bOutOfHealth;
};
