// Copyright by Suspended Team.


#include "AbilitySystem/Abilities/MeleeAbility.h"
#include "AnimSequences/PaperZDAnimSequence.h"
#include "PaperZDAnimInstance.h"
#include "Animations/RagnarokAnimInstance.h"
#include "Characters/BaseCharacter.h"
#include "Components/BoxComponent.h"
#include "Kismet/GameplayStatics.h"
#include "Weapons/BaseWeaponInstance.h"

void UMeleeAbility::ActivateAbility(const FAbilityInfo& ActivationInfo)
{
	Super::ActivateAbility(ActivationInfo);
	
	const ABaseCharacter* Character = Cast<ABaseCharacter>(ActivationInfo.AvatarPawn);
	UBaseWeaponInstance* WeaponInstance = GetCurrentEquippedWeaponInstance();
	
	if (!Character || !WeaponInstance || !WeaponInstance->GetWeaponVisualData().FireAnimSequence)
	{
		EndAbility();
		return;
	}
	
	URagnarokAnimInstance* AnimInstance = Character->GetRagnarokAnimInstance();
	if (!AnimInstance)
	{
		EndAbility();
		return;
	}

	AnimInstance->AttackNotifyDelegate.AddDynamic(this,&ThisClass::CheckHit);
	GetWorld()->GetTimerManager().SetTimer(EndAnimationTimerHandle,this,&ThisClass::EndAbility,WeaponInstance->GetWeaponVisualData().FireAnimSequence->GetTotalDuration());

	AnimInstance->PlayAnimationOverride(WeaponInstance->GetWeaponVisualData().FireAnimSequence);
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

	UBaseWeaponInstance* WeaponInstance = GetCurrentEquippedWeaponInstance();
	if (!WeaponInstance)
	{
		return;
	}

	
	UGameplayStatics::ApplyDamage(TargetCharacter,WeaponInstance->GetBaseWeaponData().BaseDamage,InstigatorCharacter->GetController(),InstigatorCharacter,WeaponInstance->GetBaseWeaponData().DamageType);
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
