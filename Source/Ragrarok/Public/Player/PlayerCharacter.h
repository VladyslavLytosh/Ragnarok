// Copyright by Suspended Team.

#pragma once

#include "CoreMinimal.h"
#include "Characters/BaseCharacter.h"
#include "..\Characters\Interfaces\ShieldBearerInterface.h"
#include "PlayerCharacter.generated.h"

UCLASS()
class RAGRAROK_API APlayerCharacter : public ABaseCharacter, public IShieldBearerInterface
{
	GENERATED_BODY()

public:
	APlayerCharacter();

	virtual void SetupPlayerInputComponent(UInputComponent* PlayerInputComponent) override;

	UFUNCTION(BlueprintPure)
	virtual USphereComponent* GetShieldSphereComponent() const override { return ShieldSphereComponent; }

	UFUNCTION(BlueprintPure)
	virtual UPaperFlipbookComponent* GetShieldFlipbookComponent() const override  { return ShieldFlipbookComponent; }
	
protected:
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category="Components|Input")
	TObjectPtr<URagnarokInputComponent> RagnarokInputComponent;

	UPROPERTY(EditDefaultsOnly,BlueprintReadWrite, Category = "Components")
	TObjectPtr<USphereComponent> ShieldSphereComponent;

	UPROPERTY(EditDefaultsOnly,BlueprintReadWrite, Category = "Components")
	TObjectPtr<UPaperFlipbookComponent> ShieldFlipbookComponent;
};
