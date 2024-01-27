// Copyright by Suspended Team.

#pragma once

#include "CoreMinimal.h"
#include "NiagaraSystem.h"
#include "RagnarokGlobals.h"
#include "AbilitySystem/AbilityBase.h"
#include "ChainLightningAbility.generated.h"

struct FNoiseReportData;
class UPaperZDAnimSequence;

USTRUCT(BlueprintType)
struct FChainLightningInfo
{
	GENERATED_BODY()
	
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Chain Lightning Info")
	int32 MaxChains = 5;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Chain Lightning Info")
	int32 ChainLightningLength = 500;
	
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Chain Lightning Info")
	int32 ChainLightningRadius = 200;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Chain Lightning Info")
	int32 BaseDamage = 100;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Chain Lightning Info")
	int32 DamageDecreasePerChain = 10;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Chain Lightning Info")
	int32 MinDamage = 50;
	
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Chain Lightning Info")
	TSubclassOf<UDamageType> DamageType;

	UPROPERTY(EditAnywhere, Category = "Firing")
	UNiagaraSystem* ChainLightningEffect;
};

USTRUCT(BlueprintType)
struct FChainLightningVisualInfo
{
	GENERATED_BODY()

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Ability Visual")
	TObjectPtr<UPaperZDAnimSequence> CastStartAnimSequence;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category="Ability Visual")
	TObjectPtr<UPaperZDAnimSequence> CastEndAnimSequence;

	UPROPERTY(EditDefaultsOnly)
	TSubclassOf<UCameraShakeBase> StartChainCameraShake;
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category="Ability Visual")
	TObjectPtr<USoundBase> StartChainSound;
	
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category="Ability Visual")
	TSubclassOf<UCameraShakeBase> ChainDamageCameraShake;
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category="Ability Visual")
	TObjectPtr<USoundBase> ChainDamageSound;
};

UCLASS()
class RAGRAROK_API UChainLightningAbility : public UAbilityBase
{
	GENERATED_BODY()

protected:
	virtual void ActivateAbility(const FAbilityInfo& ActivationInfo) override;
	
	UPROPERTY(EditDefaultsOnly, Category = "Chain Lightning Info")
	FChainLightningInfo ChainLightningInfo;

	UPROPERTY(EditDefaultsOnly, Category = "Chain Lightning Visual Info")
	FChainLightningVisualInfo ChainLightningVisualInfo;

	UPROPERTY(EditDefaultsOnly,BlueprintReadOnly)
	FNoiseReportData NoiseReportData;
	
	UFUNCTION()
	void StartCast();

	UFUNCTION()
	void OnCastEnd(bool bCompleted);
	
private:
	AActor* FindClosestActor(const TArray<FOverlapResult>& OverlapResults, AActor* SourceActor);
	
	void ChainToNextTarget(const AActor* NextTarget, FCollisionQueryParams& CollisionQueryParams, const FCollisionObjectQueryParams& ObjectQueryParams, TArray<FOverlapResult>& OutOverlapResults) const;

	void DecreaseDamage(int32& OutDamage, const int32& DecreaseAmount, const int32 MinDamage);

	
};
