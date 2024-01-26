// Copyright by Suspended Team.

#pragma once

#include "CoreMinimal.h"
#include "BaseWeaponInstance.h"
#include "MeleeWeaponInstance.generated.h"


UCLASS()
class RAGRAROK_API UMeleeWeaponInstance : public UBaseWeaponInstance
{
	GENERATED_BODY()
	
public:
	TSubclassOf<AActor> GetOverlappingActorsClass() const {return OverlappingActorsClass;}
	
protected:
	UPROPERTY(EditDefaultsOnly,BlueprintReadOnly)
	TSubclassOf<AActor> OverlappingActorsClass;
};
