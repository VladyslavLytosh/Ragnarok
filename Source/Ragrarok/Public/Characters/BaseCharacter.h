// Copyright by Suspended Team.

#pragma once

#include "CoreMinimal.h"
#include "AbilitySystem/AbilitySystemInterface.h"
#include "GameFramework/Character.h"
#include "BaseCharacter.generated.h"

class UAbilitySet;
class URagnarokInputComponent;

UCLASS()
class RAGRAROK_API ABaseCharacter : public ACharacter, public IAbilitySystemInterface
{
	GENERATED_BODY()

public:
	ABaseCharacter();
	
	virtual UAbilitySystemComponent* GetAbilitySystemComponent() const override;

	virtual void SetupPlayerInputComponent(UInputComponent* PlayerInputComponent) override;

	virtual void BeginPlay() override;
	
protected:
	UPROPERTY(EditDefaultsOnly,Category="AbilitySystem")
	UAbilitySystemComponent* AbilitySystemComponent;

	UPROPERTY(EditDefaultsOnly,Category="Input")
	URagnarokInputComponent* RagnarokInputComponent;

	UPROPERTY(EditDefaultsOnly,Category="AbilitySystem")
	TSubclassOf<UAbilitySet> DefaultAbilitySetClass;
};
