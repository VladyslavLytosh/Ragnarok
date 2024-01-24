// Copyright by Suspended Team.


#include "Characters/HealthComponent.h"

UHealthComponent::UHealthComponent(const FObjectInitializer& ObjectInitializer) : Super(ObjectInitializer)
{
}

void UHealthComponent::AddHealth(const float& Amount)
{
	if (Amount > 0)
	{
		SetHealth(CurrentHealth + Amount);
	}
}

void UHealthComponent::ReduceHealth(const float& Amount)
{
	if (Amount > 0)
	{
		SetHealth(CurrentHealth - Amount);
	}
}

#if WITH_EDITOR
void UHealthComponent::PostEditChangeProperty(FPropertyChangedEvent& PropertyChangedEvent)
{
	Super::PostEditChangeProperty(PropertyChangedEvent);
	CurrentHealth = FMath::Clamp(CurrentHealth,0.f,MaxHealth);
}
#endif

void UHealthComponent::SetHealth(const float NewHealth)
{
	const float Health = FMath::Clamp(NewHealth,0.f,MaxHealth);
	CurrentHealth = Health;

	if (Health <= 0)
	{
		bOutOfHealth = true;
	}
	else
	{
		bOutOfHealth = false;
	}
}
