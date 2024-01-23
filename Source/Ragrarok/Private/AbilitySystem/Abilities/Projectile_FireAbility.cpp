// Copyright by Suspended Team.


#include "AbilitySystem/Abilities/Projectile_FireAbility.h"

#include "PaperFlipbookComponent.h"
#include "PaperZDAnimInstance.h"
#include "Characters/BaseCharacter.h"
#include "Weapons/ProjectileWeaponInstance.h"

void UProjectile_FireAbility::ActivateAbility(const FAbilityInfo& ActivationInfo)
{
	Super::ActivateAbility(ActivationInfo);

	const ABaseCharacter* Character = Cast<ABaseCharacter>(ActivationInfo.AvatarPawn);
	if (!Character || !Character->GetSprite())
	{
		return;
	}
	UProjectileWeaponInstance* ProjectileWeaponInstance = Cast<UProjectileWeaponInstance>(GetCurrentEquippedWeaponInstance());
	if (!ProjectileWeaponInstance)
	{
		return;
	}

	if(!ProjectileWeaponInstance->CanFire())
	{
		EndAbility();
		return;
	}
	Character->GetAnimInstance()->PlayAnimationOverride(ProjectileWeaponInstance->GetWeaponVisualData().FireAnimSequence);
	const FVector SpawnLocation = Character->GetSprite()->GetSocketLocation("WeaponMuzzle");
	const FRotator SpawnRotation = Character->GetActorRotation();
	GetWorld()->SpawnActor<AActor>(ProjectileWeaponInstance->GetProjectileWeaponData().Projectile, SpawnLocation, SpawnRotation);
	
	ProjectileWeaponInstance->UpdateFiringTime();
	EndAbility();
}
 