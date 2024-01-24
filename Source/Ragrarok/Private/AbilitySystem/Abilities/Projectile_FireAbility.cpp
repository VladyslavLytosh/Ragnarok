// Copyright by Suspended Team.


#include "AbilitySystem/Abilities/Projectile_FireAbility.h"

#include "PaperFlipbookComponent.h"
#include "PaperZDAnimInstance.h"
#include "Animations/RagnarokAnimInstance.h"
#include "Characters/BaseCharacter.h"
#include "Weapons/ProjectileWeaponInstance.h"

void UProjectile_FireAbility::ActivateAbility(const FAbilityInfo& ActivationInfo)
{
	Super::ActivateAbility(ActivationInfo);

	if (!ActivationInfo.AvatarPawn)
	{
		return;
	}
	const ABaseCharacter* Character = Cast<ABaseCharacter>(ActivationInfo.AvatarPawn);
	if (!Character)
	{
		return;
	}
	const UProjectileWeaponInstance* ProjectileWeaponInstance = Cast<UProjectileWeaponInstance>(GetCurrentEquippedWeaponInstance());
	if (!ProjectileWeaponInstance)
	{
		return;
	}
	URagnarokAnimInstance* AnimInstance = Character->GetRagnarokAnimInstance();
	if (!AnimInstance || !ProjectileWeaponInstance->CanFire() || !ProjectileWeaponInstance->GetWeaponVisualData().FireAnimSequence)
	{
		EndAbility();
		return;
	}
	Character->GetAnimInstance()->PlayAnimationOverride(
		ProjectileWeaponInstance->GetWeaponVisualData().FireAnimSequence, "DefaultSlot", 1, 0,
		FZDOnAnimationOverrideEndSignature::CreateUObject(this, &ThisClass::OnFireAnimEnded));
	
	AnimInstance->AttackNotifyDelegate.AddDynamic(this, &ThisClass::WeaponFire);
}

void UProjectile_FireAbility::WeaponFire()
{
	if (!GetCurrentAbilityInfo().AvatarPawn)
	{
		return;
	}
	const ABaseCharacter* Character = Cast<ABaseCharacter>(GetCurrentAbilityInfo().AvatarPawn);
	if (!Character || !Character->GetSprite())
	{
		return;
	}
	UProjectileWeaponInstance* ProjectileWeaponInstance = Cast<UProjectileWeaponInstance>(GetCurrentEquippedWeaponInstance());
	if (!ProjectileWeaponInstance || !ProjectileWeaponInstance->GetProjectileWeaponData().ProjectileClass)
	{
		return;
	}
	
	const FVector SpawnLocation = Character->GetSprite()->GetSocketLocation("WeaponMuzzle");
	const FRotator SpawnRotation = Character->GetActorRotation();
	GetWorld()->SpawnActor<AActor>(ProjectileWeaponInstance->GetProjectileWeaponData().ProjectileClass, SpawnLocation,
	                               SpawnRotation);
	
	ProjectileWeaponInstance->UpdateFiringTime();
}

void UProjectile_FireAbility::OnFireAnimEnded(bool bComplete)
{
	if (bComplete)
	{
		const ABaseCharacter* Character = Cast<ABaseCharacter>(GetCurrentAbilityInfo().AvatarPawn);
		if (!Character)
		{
			return;
		}

		if (URagnarokAnimInstance* AnimInstance = Character->GetRagnarokAnimInstance())
		{
			AnimInstance->AttackNotifyDelegate.Clear();
		}
		EndAbility();
	}
}
 