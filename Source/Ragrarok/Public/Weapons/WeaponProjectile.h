// Copyright by Suspended Team.

#pragma once

#include "CoreMinimal.h"
#include "RagnarokGlobals.h"
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
	
	UPROPERTY(EditDefaultsOnly, Category = "Projectile visual info", meta=(AllowPrivateAccess=true))
	TObjectPtr<UPaperFlipbook> ProjectileHitEffect;
	
	UPROPERTY(EditDefaultsOnly, Category = "Projectile visual info", meta=(AllowPrivateAccess=true))
	FVector ProjectileHitEffectScale3D = FVector(2,2,2);
	
};

USTRUCT(BlueprintType)
struct FProjectileDamageData
{
	GENERATED_BODY()

	UPROPERTY(BlueprintReadOnly)
	float BaseDamage;
	
	UPROPERTY(BlueprintReadOnly)
	TSubclassOf<UDamageType> DamageType;
	
	UPROPERTY(BlueprintReadOnly)
	bool bIsDamageRadial;

	UPROPERTY(BlueprintReadOnly)
	float DamageRadius;
};

USTRUCT(BlueprintType)
struct FProjectileVisuals
{
	GENERATED_BODY()

	UPROPERTY(EditDefaultsOnly,BlueprintReadOnly)
	TObjectPtr<USoundBase> HitSound;
	
	UPROPERTY(EditDefaultsOnly,BlueprintReadOnly)
	TSubclassOf<UCameraShakeBase> HitCameraShake; 
};
UCLASS()
class RAGRAROK_API AWeaponProjectile : public AActor
{
	GENERATED_BODY()

public:
	AWeaponProjectile();

	void SetProjectileDamageData(const FProjectileDamageData& ProjectileDamageData) {DamageData = ProjectileDamageData;}
	void SetProjectileVisuals(const FProjectileVisuals& Visuals) {ProjectileVisuals = Visuals;}
protected:
	virtual void PostInitializeComponents() override;
	
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Components")
	TObjectPtr<UProjectileMovementComponent> ProjectileMovementComponent;
	
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Components")
	TObjectPtr<USphereComponent> HitRegionComponent;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite)
	TObjectPtr<UPaperFlipbookComponent> ProjectileSprite;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite)
	FProjectileVisuals ProjectileVisuals;
	
	UFUNCTION()
	void OnHitRegionBeginOverlap(UPrimitiveComponent* OverlappedComponent,
							  AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep,
							  const FHitResult& SweepResult);

	UPROPERTY(EditDefaultsOnly, Category = "Projectile info")
	FProjectileInfo ProjectileInfo;

	UPROPERTY(BlueprintReadOnly)
	FProjectileDamageData DamageData;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	FNoiseReportData NoiseReportData;

	UPROPERTY(EditDefaultsOnly,BlueprintReadOnly,Category="ClassFilter")
	TSubclassOf<AActor> ClassFilter;
private:
	FTransform GetProjectileHitEffectSpawnTransform() const;

	void SpawnProjectileHitEffect();
};
