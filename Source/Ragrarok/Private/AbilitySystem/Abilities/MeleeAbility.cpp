// Copyright by Suspended Team.


#include "AbilitySystem/Abilities/MeleeAbility.h"
#include "AnimSequences/PaperZDAnimSequence.h"
#include "PaperZDAnimInstance.h"
#include "Animations/RagnarokAnimInstance.h"
#include "Characters/BaseCharacter.h"
#include "Components/BoxComponent.h"
#include "Kismet/GameplayStatics.h"

void UMeleeAbility::ActivateAbility(const FAbilityInfo& ActivationInfo)
{
	Super::ActivateAbility(ActivationInfo);
	
	const ABaseCharacter* Character = Cast<ABaseCharacter>(ActivationInfo.AvatarPawn);
	if (!Character || !MeleeAttackAnimation)
	{
		EndAbility();
	}
	
	URagnarokAnimInstance* AnimInstance = Character->GetRagnarokAnimInstance();
	if (!AnimInstance)
	{
		EndAbility();
	}

	AnimInstance->AttackNotifyDelegate.AddDynamic(this,&ThisClass::CheckHit);
	GetWorld()->GetTimerManager().SetTimer(EndAnimationTimerHandle,this,&ThisClass::EndAbility,MeleeAttackAnimation->GetTotalDuration());

	AnimInstance->PlayAnimationOverride(MeleeAttackAnimation);
}

void UMeleeAbility::EndAbility()
{
	Super::EndAbility();
	GetWorld()->GetTimerManager().ClearTimer(EndAnimationTimerHandle);

	const ABaseCharacter* Character = Cast<ABaseCharacter>(GetCurrentAbilityInfo().AvatarPawn);
	if (!Character)
	{
		return;
	}

	if (URagnarokAnimInstance* AnimInstance = Character->GetRagnarokAnimInstance())
	{
		AnimInstance->AttackNotifyDelegate.Clear();
	}
}

void UMeleeAbility::ApplyMeleeAttackToTarget(ABaseCharacter* InstigatorCharacter, ABaseCharacter* TargetCharacter)
{
	UE_LOG(LogTemp,Display,TEXT("Attacked character: %s"),*TargetCharacter->GetName());

	UGameplayStatics::ApplyDamage(TargetCharacter,DamageAmount,InstigatorCharacter->GetController(),InstigatorCharacter,DamageType);
}

void UMeleeAbility::CheckHit()
{
	ABaseCharacter* Character = Cast<ABaseCharacter>(GetCurrentAbilityInfo().AvatarPawn);
	if (!Character)
	{
		return;
	}
	
	const UBoxComponent* HitBox = Character->GetHitBoxComponent();
	if (!HitBox)
	{
		return;
	}

	
	TArray<AActor*> OverlappedActors;
	HitBox->GetOverlappingActors(OverlappedActors,CharacterClass);

	for (AActor* OverlappedActor : OverlappedActors)
	{
		if (ABaseCharacter* OverlappedCharacter = Cast<ABaseCharacter>(OverlappedActor))
		{
			if (OverlappedCharacter != Character)
			{
				ApplyMeleeAttackToTarget(Character,OverlappedCharacter);
			}
		}
	}
}
