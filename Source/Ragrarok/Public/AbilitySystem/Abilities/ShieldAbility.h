// Copyright by Suspended Team.

#pragma once

#include "CoreMinimal.h"
#include "PaperFlipbook.h"
#include "AbilitySystem/AbilityBase.h"
#include "ShieldAbility.generated.h"

class UPaperFlipbookComponent;
class UPaperZDAnimSequence;
class USphereComponent;

USTRUCT(BlueprintType)
struct FAbilityVisualInfo
{
	GENERATED_BODY()

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Ability Visual")
	TObjectPtr<UPaperZDAnimSequence> ShieldUpAnimSequence;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category="Ability Visual")
	TObjectPtr<UPaperZDAnimSequence> ShieldDownAnimSequence;
	
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category="Ability Visual")
	TObjectPtr<UPaperFlipbook> ShieldUpFlipbook;
	
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category="Ability Visual")
	TObjectPtr<UPaperFlipbook> ShieldDownFlipbook;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category="Ability Visual")
	TObjectPtr<UPaperFlipbook> ShieldActiveFlipbook;
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
	
	UPROPERTY(EditDefaultsOnly, Category = "Ability Settings", meta=(Units = "s"))
	int32 MaxAbilityLength = 10;
	
private:
	FTimerHandle EndAbilityTimer;

	void SetAndPlayFlipbookAnimation(UPaperFlipbookComponent* PaperFlipbookComponent, bool bIsLopping, UPaperFlipbook* Flipbook);

	UFUNCTION(BlueprintPure)
	UPaperFlipbookComponent* GetShieldFlipbook(const APawn* Pawn) const;
	UFUNCTION(BlueprintPure)
	USphereComponent* GetShieldSphere(const APawn* Pawn) const;
};
