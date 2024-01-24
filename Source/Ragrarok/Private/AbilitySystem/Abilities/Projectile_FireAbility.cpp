// Copyright by Suspended Team.


#include "AbilitySystem/Abilities/Projectile_FireAbility.h"

#include "PaperFlipbookComponent.h"
#include "PaperZDAnimInstance.h"
#include "Animations/RagnarokAnimInstance.h"
#include "Characters/BaseCharacter.h"
#include "Weapons/ProjectileWeaponInstance.h"
#include "Weapons/WeaponProjectile.h"

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
	ABaseCharacter* Character = Cast<ABaseCharacter>(GetCurrentAbilityInfo().AvatarPawn);
	if (!Character || !Character->GetSprite())
	{
		return;
	}
	UProjectileWeaponInstance* ProjectileWeaponInstance = Cast<UProjectileWeaponInstance>(GetCurrentEquippedWeaponInstance());
	if (!ProjectileWeaponInstance || !ProjectileWeaponInstance->GetProjectileWeaponData().ProjectileClass)
	{
		return;
	}
	
	if (AWeaponProjectile* ProjectileActor = GetWorld()->SpawnActorDeferred<AWeaponProjectile>(ProjectileWeaponInstance->GetProjectileWeaponData().ProjectileClass, FTransform::Identity))
	{
		ProjectileActor->SetOwner(Character);
		ProjectileActor->FinishSpawning(GetProjectileSpawnTransform(Character));
	}
	
	ProjectileWeaponInstance->UpdateFiringTime();
}

void UProjectile_FireAbility::OnFireAnimEnded(bool bCompleted)
{
	if (bCompleted)
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

FTransform UProjectile_FireAbility::GetProjectileSpawnTransform(const ABaseCharacter* Character) const
{
	FTransform SpawnTransform;
	SpawnTransform.SetLocation(Character->GetSprite()->GetSocketLocation("WeaponMuzzle"));
	SpawnTransform.SetRotation(Character->GetActorRotation().Quaternion());
	SpawnTransform.SetScale3D(FVector(1,1,1));
	
	return SpawnTransform;
}
 