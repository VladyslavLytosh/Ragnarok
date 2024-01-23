// Copyright by Suspended Team.


#include "Weapons/BaseWeaponInstance.h"

#include "Characters/BaseCharacter.h"

bool UBaseWeaponInstance::CanFire() const
{
	return IsFireRateValid();
}

ABaseCharacter* UBaseWeaponInstance::GetBaseCharacter() const
{
	APawn* Pawn = GetPawn();
	if (!Pawn)
	{
		UE_LOG(LogTemp,Error,TEXT("Weapon instance does not have pawn owner"));
		return nullptr;
	}

	ABaseCharacter* BaseCharacter = Cast<ABaseCharacter>(Pawn);
	if (!BaseCharacter)
	{
		UE_LOG(LogTemp,Error,TEXT("Weapon intacnce does not have BaseCharacter owner"));
		return nullptr;
	}
	return BaseCharacter;
}

APawn* UBaseWeaponInstance::GetPawn() const
{
	return Cast<APawn>(GetOuter());
}

bool UBaseWeaponInstance::IsFireRateValid() const
{
	return GetCurrentFireRate() <= BaseWeaponData.FireRate;
}

float UBaseWeaponInstance::GetCurrentFireRate() const
{
	const float CurrentFireRate =  1 / GetTimeSinceLastFired();
	return CurrentFireRate;
}

float UBaseWeaponInstance::GetTimeSinceLastFired() const
{
	check(GetWorld());

	const float TimeSinceLastFired = GetWorld()->TimeSince(TimeLastFired);
	return TimeSinceLastFired;
}

void UBaseWeaponInstance::UpdateFiringTime()
{
	const UWorld* World = GetWorld();
	check(World);
	
	TimeLastFired = World->GetTimeSeconds();
}
