// Copyright by Suspended Team.

#pragma once

#include "CoreMinimal.h"
#include "AbilitySystem/AbilityBase.h"
#include "ShieldAbility.generated.h"

class UPaperZDAnimSequence;

USTRUCT(BlueprintType)
struct FAbilityVisualInfo
{
	GENERATED_BODY()

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Ability Visual")
	TObjectPtr<UPaperZDAnimSequence> ShieldUpAnimSequence;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category="Ability Visual")
	TObjectPtr<UPaperZDAnimSequence> ShieldDownAnimSequence;
};

UCLASS()
class RAGRAROK_API UShieldAbility : public UAbilityBase
{
	GENERATED_BODY()
	
public:
	virtual void InputReleased() override;

protected:
	virtual void ActivateAbility(const FAbilityInfo& ActivationInfo) override;

	virtual void EndAbility() override;
	
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Ability Visual")
	FAbilityVisualInfo AbilityVisualInfo;

	UFUNCTION()
	void OnShieldUpAnimEnded(bool bCompleted);

	UFUNCTION()
	void OnShieldBeginOverlap(UPrimitiveComponent* OverlappedComponent,
	                          AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep,
	                          const FHitResult& SweepResult);
};
