// Copyright by Suspended Team.


#include "AbilitySystem/Abilities/ChainLightningAbility.h"

#include "Characters/BaseCharacter.h"
#include "Kismet/GameplayStatics.h"
#include "NiagaraFunctionLibrary.h"
#include "NiagaraComponent.h"
#include "PaperFlipbookComponent.h"
#include "Animations/RagnarokAnimInstance.h"
#include "Perception/AISense_Hearing.h"

void UChainLightningAbility::ActivateAbility(const FAbilityInfo& ActivationInfo)
{
	Super::ActivateAbility(ActivationInfo);

	APawn* AvatarPawn = GetCurrentAbilityInfo().AvatarPawn;
	if (!AvatarPawn || !GetWorld())
	{
		EndAbility();
		return;
	}
	const ABaseCharacter* Character = Cast<ABaseCharacter>(AvatarPawn);
	if (!Character)
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
	Character->GetAnimInstance()->PlayAnimationOverride(ChainLightningVisualInfo.CastStartAnimSequence);
	AnimInstance->AttackNotifyDelegate.AddDynamic(this, &ThisClass::StartCast);
}

void UChainLightningAbility::StartCast()
{
	APawn* AvatarPawn = GetCurrentAbilityInfo().AvatarPawn;
	if (!AvatarPawn || !GetWorld())
	{
		EndAbility();
		return;
	}
	ABaseCharacter* Character = Cast<ABaseCharacter>(AvatarPawn);
	if (!Character)
	{
		EndAbility();
		return;
	}

	PlayCameraShake(ChainLightningVisualInfo.StartChainCameraShake);
	PlaySoundAtPawnLocation(ChainLightningVisualInfo.StartChainSound);
	UAISense_Hearing::ReportNoiseEvent(GetWorld(),Character->GetActorLocation(),NoiseReportData.Loudness,Character,NoiseReportData.NoiseRange);

	FHitResult OutHitResult;
	const FVector Start = Character->GetActorLocation();
	const FVector End = Start + Character->GetActorForwardVector() * ChainLightningInfo.ChainLightningLength;

	FCollisionQueryParams CollisionQueryParams;
	CollisionQueryParams.AddIgnoredActor(Character);

	FCollisionObjectQueryParams ObjectQueryParams;
	ObjectQueryParams.AddObjectTypesToQuery(ECC_Pawn);

	auto ApplyDamageToTarget = [this, &Character](AActor* Target, const int32& DamageAmount)
	{
		UGameplayStatics::ApplyDamage(Target, DamageAmount, Character->GetController(), Character,
		                              ChainLightningInfo.DamageType);
	};
	
	if (!ChainLightningInfo.ChainLightningEffect || !Character->GetSprite())
	{
		EndAbility();
		return;
	}
	UNiagaraComponent* FirstTargetChainLightning = UNiagaraFunctionLibrary::SpawnSystemAtLocation(this, ChainLightningInfo.ChainLightningEffect, Character->GetSprite()->GetSocketLocation("CastStart"));
	FirstTargetChainLightning->SetNiagaraVariableVec3(FString("BeamEnd"), End);
	
	if (GetWorld()->LineTraceSingleByObjectType(OutHitResult, Start, End, ObjectQueryParams, CollisionQueryParams))
	{
		CollisionQueryParams.AddIgnoredActor(OutHitResult.GetActor());

		TArray<FOverlapResult> OutOverlapResults;
		GetWorld()->OverlapMultiByObjectType(OutOverlapResults, OutHitResult.ImpactPoint, FQuat::Identity,
											 ObjectQueryParams,
											 FCollisionShape::MakeSphere(ChainLightningInfo.ChainLightningRadius),
											 CollisionQueryParams);
		if (!OutHitResult.GetActor())
		{
			EndAbility();
			return;
		}
		AActor* PrevTarget = OutHitResult.GetActor();

		FirstTargetChainLightning->SetNiagaraVariableVec3(FString("BeamEnd"), PrevTarget->GetActorLocation());

		int32 Damage = ChainLightningInfo.BaseDamage;
		// Apply damage to first target
		ApplyDamageToTarget(PrevTarget, Damage);

		for (int i = 0; i < ChainLightningInfo.MaxChains; ++i)
		{
			AActor* NextTarget = FindClosestActor(OutOverlapResults, PrevTarget);
			if (!NextTarget)
			{
				break;
			}
			
			DecreaseDamage(Damage, ChainLightningInfo.DamageDecreasePerChain, ChainLightningInfo.MinDamage);
			ApplyDamageToTarget(NextTarget, Damage);
			
			UNiagaraComponent* ChainLightningEffect = UNiagaraFunctionLibrary::SpawnSystemAtLocation(this, ChainLightningInfo.ChainLightningEffect, PrevTarget->GetActorLocation());
			ChainLightningEffect->SetNiagaraVariableVec3(FString("BeamEnd"), NextTarget->GetActorLocation());
			
			ChainToNextTarget(NextTarget, CollisionQueryParams, ObjectQueryParams, OutOverlapResults);
			if (OutOverlapResults.IsEmpty())
			{
				break;
			}
			PrevTarget = NextTarget;
		}
	}
	
	Character->GetAnimInstance()->PlayAnimationOverride(
	ChainLightningVisualInfo.CastEndAnimSequence, "DefaultSlot", 1, 0,
	FZDOnAnimationOverrideEndSignature::CreateUObject(this, &ThisClass::OnCastEnd));
}

void UChainLightningAbility::OnCastEnd(bool bCompleted)
{
	if (const ABaseCharacter* Character = Cast<ABaseCharacter>(GetCurrentAbilityInfo().AvatarPawn))
	{
		if (URagnarokAnimInstance* AnimInstance = Character->GetRagnarokAnimInstance())
		{
			AnimInstance->AttackNotifyDelegate.Clear();
		}
	}
	EndAbility();
}

AActor* UChainLightningAbility::FindClosestActor(const TArray<FOverlapResult>& OverlapResults, AActor* SourceActor)
{
	if (OverlapResults.Num() == 0 || !SourceActor)
	{
		return nullptr;
	}

	FOverlapResult ClosestActor = OverlapResults[0];
	if (OverlapResults.Num() == 1)
	{
		return ClosestActor.GetActor();
	}

	auto DistanceComparator = [SourceActor](const FOverlapResult& A, const FOverlapResult& B) -> bool
	{
		if (!A.GetActor() || !B.GetActor())
		{
			return false;
		}
		const float DistanceA = FVector::DistSquared(SourceActor->GetActorLocation(), A.GetActor()->GetActorLocation());
		const float DistanceB = FVector::DistSquared(SourceActor->GetActorLocation(), B.GetActor()->GetActorLocation());
		return DistanceA < DistanceB;
	};

	for (int i = 1; i < OverlapResults.Num(); ++i)
	{
		if (DistanceComparator(OverlapResults[i], ClosestActor))
		{
			ClosestActor = OverlapResults[i];
		}
	}

	return ClosestActor.GetActor();
}

void UChainLightningAbility::ChainToNextTarget(const AActor* NextTarget,
                                               FCollisionQueryParams& CollisionQueryParams,
                                               const FCollisionObjectQueryParams& ObjectQueryParams,
                                               TArray<FOverlapResult>& OutOverlapResults) const
{
	OutOverlapResults.Empty();
	
	CollisionQueryParams.AddIgnoredActor(NextTarget);
	GetWorld()->OverlapMultiByObjectType(OutOverlapResults, NextTarget->GetActorLocation(), FQuat::Identity,
	                                     ObjectQueryParams,
	                                     FCollisionShape::MakeSphere(ChainLightningInfo.ChainLightningRadius),
	                                     CollisionQueryParams);
}

void UChainLightningAbility::DecreaseDamage(int32& OutDamage, const int32& DecreaseAmount, const int32 MinDamage)
{
	OutDamage = FMath::Max(MinDamage, OutDamage - DecreaseAmount);
	PlayCameraShake(ChainLightningVisualInfo.ChainDamageCameraShake);
	PlaySoundAtPawnLocation(ChainLightningVisualInfo.ChainDamageSound);
}
