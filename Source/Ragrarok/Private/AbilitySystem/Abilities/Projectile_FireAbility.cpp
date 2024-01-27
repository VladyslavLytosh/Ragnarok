// Copyright by Suspended Team.


#include "AbilitySystem/Abilities/Projectile_FireAbility.h"

#include "PaperFlipbookComponent.h"
#include "PaperZDAnimInstance.h"
#include "Animations/RagnarokAnimInstance.h"
#include "Characters/BaseCharacter.h"
#include "Perception/AISense_Hearing.h"
#include "Weapons/ProjectileWeaponInstance.h"
#include "Weapons/WeaponProjectile.h"

void UProjectile_FireAbility::ActivateAbility(const FAbilityInfo& ActivationInfo)
{
	Super::ActivateAbility(ActivationInfo);

	if (!ActivationInfo.AvatarPawn)
	{
		EndAbility();
		return;
	}
	const ABaseCharacter* Character = Cast<ABaseCharacter>(ActivationInfo.AvatarPawn);
	if (!Character)
	{
		EndAbility();
		return;
	}
	const UProjectileWeaponInstance* ProjectileWeaponInstance = Cast<UProjectileWeaponInstance>(GetCurrentEquippedWeaponInstance());
	if (!ProjectileWeaponInstance)
	{
		EndAbility();
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
	PlayCameraShake(ProjectileWeaponInstance->GetWeaponVisualData().FireCameraShake);
	PlaySoundAtPawnLocation(ProjectileWeaponInstance->GetWeaponVisualData().FireSound);
}

void UProjectile_FireAbility::WeaponFire()
{
	if (!GetCurrentAbilityInfo().AvatarPawn)
	{
		EndAbility();
		return;
	}
	ABaseCharacter* Character = Cast<ABaseCharacter>(GetCurrentAbilityInfo().AvatarPawn);
	if (!Character || !Character->GetSprite())
	{
		EndAbility();
		return;
	}
	UProjectileWeaponInstance* ProjectileWeaponInstance = Cast<UProjectileWeaponInstance>(GetCurrentEquippedWeaponInstance());
	if (!ProjectileWeaponInstance || !ProjectileWeaponInstance->GetProjectileWeaponData().ProjectileClass)
	{
		EndAbility();
		return;
	}

	const FProjectileWeaponData& ProjectileWeaponData = ProjectileWeaponInstance->GetProjectileWeaponData();
	if (AWeaponProjectile* ProjectileActor = GetWorld()->SpawnActorDeferred<AWeaponProjectile>(ProjectileWeaponData.ProjectileClass, FTransform::Identity))
	{
		FProjectileDamageData DamageData;
		DamageData.bIsDamageRadial = ProjectileWeaponData.bIsDamageRadial;
		DamageData.DamageRadius = ProjectileWeaponData.DamageRadius;

		DamageData.BaseDamage = ProjectileWeaponInstance->GetBaseWeaponData().BaseDamage;
		DamageData.DamageType = ProjectileWeaponInstance->GetBaseWeaponData().DamageType;
		
		ProjectileActor->SetProjectileDamageData(DamageData);
		ProjectileActor->SetOwner(Character);
		ProjectileActor->FinishSpawning(GetProjectileSpawnTransform(Character));
	}
	
	ProjectileWeaponInstance->UpdateFiringTime();
	UAISense_Hearing::ReportNoiseEvent(GetWorld(),Character->GetActorLocation(),NoiseReportData.Loudness,Character,NoiseReportData.NoiseRange);
}

void UProjectile_FireAbility::OnFireAnimEnded(bool bCompleted)
{
	const ABaseCharacter* Character = Cast<ABaseCharacter>(GetCurrentAbilityInfo().AvatarPawn);
	if (!Character)
	{
		EndAbility();
		return;
	}

	if (URagnarokAnimInstance* AnimInstance = Character->GetRagnarokAnimInstance())
	{
		AnimInstance->AttackNotifyDelegate.Clear();
	}
	EndAbility();
}

FTransform UProjectile_FireAbility::GetProjectileSpawnTransform(const ABaseCharacter* Character) const
{
	FTransform SpawnTransform;
	SpawnTransform.SetLocation(Character->GetSprite()->GetSocketLocation("WeaponMuzzle"));
	SpawnTransform.SetRotation(Character->GetActorRotation().Quaternion());
	SpawnTransform.SetScale3D(FVector(1,1,1));
	
	return SpawnTransform;
}
 