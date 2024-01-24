// Copyright by Suspended Team.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "WeaponProjectile.generated.h"

class UPaperFlipbook;
class UPaperFlipbookComponent;
class USphereComponent;
class UProjectileMovementComponent;

USTRUCT()
struct FProjectileInfo
{
	GENERATED_BODY()

	UPROPERTY(EditDefaultsOnly, Category = "Projectile damage info", meta=(AllowPrivateAccess=true))
	int32 Damage;

	UPROPERTY(EditDefaultsOnly, Category = "Projectile damage info", meta=(AllowPrivateAccess=true))
	TSubclassOf<UDamageType> DamageType;

	UPROPERTY(EditDefaultsOnly, Category = "Projectile visual info", meta=(AllowPrivateAccess=true))
	TObjectPtr<UPaperFlipbook> ProjectileHitEffect;
	
	UPROPERTY(EditDefaultsOnly, Category = "Projectile visual info", meta=(AllowPrivateAccess=true))
	FVector ProjectileHitEffectScale3D = FVector(2,2,2);
	
	UPROPERTY(EditDefaultsOnly, Category = "Projectile visual info", meta=(AllowPrivateAccess=true))
	bool bIsDamageRadial = false;
	
	UPROPERTY(EditDefaultsOnly, Category = "Projectile damage info", meta=(AllowPrivateAccess=true, EditCondition = "bIsDamageRadial"))
	int32 DamageRadius;
};

UCLASS()
class RAGRAROK_API AWeaponProjectile : public AActor
{
	GENERATED_BODY()

public:
	AWeaponProjectile();
	
protected:
	virtual void PostInitializeComponents() override;
	
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Components")
	TObjectPtr<UProjectileMovementComponent> ProjectileMovementComponent;
	
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Components")
	TObjectPtr<USphereComponent> HitRegionComponent;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite)
	TObjectPtr<UPaperFlipbookComponent> ProjectileSprite;
	
	UFUNCTION()
	void OnHitRegionBeginOverlap(UPrimitiveComponent* OverlappedComponent,
							  AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep,
							  const FHitResult& SweepResult);

	UPROPERTY(EditDefaultsOnly, Category = "Projectile info")
	FProjectileInfo ProjectileInfo;

private:
	FTransform GetProjectileHitEffectSpawnTransform() const;

	void SpawnProjectileHitEffect();
};
