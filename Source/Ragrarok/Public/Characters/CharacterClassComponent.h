// Copyright by Suspended Team.

#pragma once

#include "CoreMinimal.h"
#include "BaseCharacter.h"
#include "Components/PawnComponent.h"
#include "CharacterClassComponent.generated.h"


class UCharacterClass;
class UPaperFlipbook;

UCLASS(ClassGroup=(Custom), meta=(BlueprintSpawnableComponent))
class RAGRAROK_API UCharacterClassComponent : public UPawnComponent
{
	GENERATED_BODY()

public:
	UCharacterClassComponent(const FObjectInitializer& ObjectInitializer);
	
	virtual void BeginPlay() override;
	
	UCharacterClass* GetCurrentCharacterClass() const { return CurrentCharacterClass ;}

	const TArray<TSubclassOf<UCharacterClass>>& GetAvailableCharacterClasses() const { return AvailableCharacterClasses; }

	void SetCurrentCharacterClass(UCharacterClass* InCurrentCharacterClass, const ABaseCharacter* Character);
	
protected:
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Character Class")
	TArray<TSubclassOf<UCharacterClass>> AvailableCharacterClasses;
	
	UPROPERTY(BlueprintReadWrite)
	TObjectPtr<UCharacterClass> CurrentCharacterClass;
	
	UPROPERTY(EditDefaultsOnly, Category = "ChangeClass Effect")
	TObjectPtr<UPaperFlipbook> ChangeClassEffectFlipbook;
	
	UPROPERTY(EditAnywhere, Category = "ChangeClass Effect")
	FVector EffectScale = FVector(3,3,3);

private:
	void RemovePreviousClassAbilities(const ABaseCharacter* Character);
};