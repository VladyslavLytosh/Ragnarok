// Copyright by Suspended Team.


#include "Weapons/WeaponProjectile.h"

#include "PaperFlipbook.h"
#include "PaperFlipbookComponent.h"
#include "Characters/BaseCharacter.h"
#include "Components/SphereComponent.h"
#include "GameFramework/ProjectileMovementComponent.h"
#include "Kismet/GameplayStatics.h"
#include "Perception/AISense_Hearing.h"
#include "Subsystems/SpriteEffectsManagerSubsystem.h"


AWeaponProjectile::AWeaponProjectile()
{
	ProjectileMovementComponent = CreateDefaultSubobject<UProjectileMovementComponent>(TEXT("ProjectileMovementComponent"));
	HitRegionComponent = CreateDefaultSubobject<USphereComponent>(TEXT("HitRegionComponent"));
	ProjectileSprite = CreateDefaultSubobject<UPaperFlipbookComponent>(TEXT("UPaperFlipbookComponent"));

	check(ProjectileMovementComponent || HitRegionComponent || ProjectileSprite)
	
	HitRegionComponent->SetupAttachment(RootComponent);
	ProjectileSprite->SetupAttachment(HitRegionComponent);
	
	ProjectileMovementComponent->ProjectileGravityScale = 0;
}

void AWeaponProjectile::PostInitializeComponents()
{
	Super::PostInitializeComponents();

	if (HitRegionComponent)
	{
		HitRegionComponent->OnComponentBeginOverlap.AddDynamic(this, &ThisClass::OnHitRegionBeginOverlap);
	}
}

void AWeaponProjectile::OnHitRegionBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,
	UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	ABaseCharacter* OwnerCharacter = Cast<ABaseCharacter>(GetOwner());
	if (!OwnerCharacter || OtherActor == OwnerCharacter)
	{
		return;
	}
	
	if (DamageData.bIsDamageRadial)
	{
		TArray<AActor*> IgnoreActors;
		IgnoreActors.Add(GetOwner());
		IgnoreActors.Add(this);
		
		UGameplayStatics::ApplyRadialDamage(this, DamageData.BaseDamage, GetActorLocation(), DamageData.DamageRadius,
										DamageData.DamageType, IgnoreActors);
	}
	else
	{
		UGameplayStatics::ApplyDamage(OtherActor, DamageData.BaseDamage, OwnerCharacter->GetController(),
										this, DamageData.DamageType);
	}
	if (ProjectileVisuals.HitSound)
	{
		UGameplayStatics::PlaySoundAtLocation(GetWorld(),ProjectileVisuals.HitSound,GetActorLocation(),GetActorRotation());
	}
	if (ProjectileVisuals.HitCameraShake)
	{
		if (APlayerController* PlayerController = Cast<APlayerController>(OwnerCharacter->GetController()))
		{
			PlayerController->ClientStartCameraShake(ProjectileVisuals.HitCameraShake);
		}
	}
	UAISense_Hearing::ReportNoiseEvent(GetWorld(),GetActorLocation(),NoiseReportData.Loudness,OwnerCharacter,NoiseReportData.NoiseRange);

	SpawnProjectileHitEffect();
	Destroy();
}

FTransform AWeaponProjectile::GetProjectileHitEffectSpawnTransform() const
{
	FTransform SpawnTransform;
	SpawnTransform.SetLocation(ProjectileSprite->GetComponentLocation());
	SpawnTransform.SetRotation(ProjectileSprite->GetComponentRotation().Quaternion());
	SpawnTransform.SetScale3D(ProjectileInfo.ProjectileHitEffectScale3D);
	return SpawnTransform;
}

void AWeaponProjectile::SpawnProjectileHitEffect()
{
	if (USpriteEffectsManagerSubsystem* SpriteEffectsManagerSubsystem = USpriteEffectsManagerSubsystem::Get(this))
	{
		SpriteEffectsManagerSubsystem->SpawnSpriteEffectAtLocation(ProjectileInfo.ProjectileHitEffect,
																   GetProjectileHitEffectSpawnTransform(), this, nullptr,
																   FAttachmentTransformRules::KeepWorldTransform,
																   ProjectileInfo.ProjectileHitEffect->
																   GetTotalDuration());
	}
}
