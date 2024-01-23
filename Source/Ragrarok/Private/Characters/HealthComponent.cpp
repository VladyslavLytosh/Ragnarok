// Copyright by Suspended Team.


#include "Characters/HealthComponent.h"

UHealthComponent::UHealthComponent(const FObjectInitializer& ObjectInitializer) : Super(ObjectInitializer)
{
}

void UHealthComponent::AddHealth(const float& Amount)
{
	if (Amount > 0)
	{
		const float HealthToAdd = FMath::Clamp(Amount,0.f,MaxHealth);
		CurrentHealth += HealthToAdd;
	}
}

void UHealthComponent::ReduceHealth(const float& Amount)
{
	if (Amount > 0)
	{
		const float HealthToReduce = FMath::Clamp(Amount,0.f,MaxHealth);
		CurrentHealth -= HealthToReduce;
	}
}

#if WITH_EDITOR
void UHealthComponent::PostEditChangeProperty(FPropertyChangedEvent& PropertyChangedEvent)
{
	Super::PostEditChangeProperty(PropertyChangedEvent);
	CurrentHealth = FMath::Clamp(CurrentHealth,0.f,MaxHealth);
}
#endif