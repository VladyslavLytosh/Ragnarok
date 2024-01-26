// Copyright by Suspended Team.


#include "AbilitySystem/Abilities/ShieldAbility.h"

#include "PaperFlipbookComponent.h"
#include "PaperZDAnimInstance.h"
#include "Characters/BaseCharacter.h"
#include "Characters/Interfaces/ShieldBearerInterface.h"
#include "Components/SphereComponent.h"

void UShieldAbility::InputReleased()
{
	Super::InputReleased();

	EndAbility();
}

void UShieldAbility::ActivateAbility(const FAbilityInfo& ActivationInfo)
{
	Super::ActivateAbility(ActivationInfo);
	
	APawn* AvatarPawn = GetCurrentAbilityInfo().AvatarPawn;
	if (!AvatarPawn)
	{
		return;
	}
	const ABaseCharacter* Character = Cast<ABaseCharacter>(AvatarPawn);
	if (!Character)
	{
		return;
	}
	const URagnarokAnimInstance* AnimInstance = Character->GetRagnarokAnimInstance();
	if (!AnimInstance || !ShieldVisualInfo.ShieldUpAnimSequence)
	{
		EndAbility();
		return;
	}
	Character->GetAnimInstance()->PlayAnimationOverride(
	ShieldVisualInfo.ShieldUpAnimSequence, "DefaultSlot", 1, 0,
	FZDOnAnimationOverrideEndSignature::CreateUObject(this, &ThisClass::OnShieldUpAnimEnded));

	PlayCameraShake(ShieldVisualInfo.ShieldUpCameraShake);
	PlaySoundAtPawnLocation(ShieldVisualInfo.ShieldUpSound);
	if (GetShieldFlipbook(Character))
	{
		SetAndPlayFlipbookAnimation(GetShieldFlipbook(Character), false, ShieldVisualInfo.ShieldUpFlipbook);
	}
}

void UShieldAbility::EndAbility()
{
	Super::EndAbility();
	
	APawn* AvatarPawn = GetCurrentAbilityInfo().AvatarPawn;
	if (!AvatarPawn)
	{
		return;
	}
	const ABaseCharacter* Character = Cast<ABaseCharacter>(AvatarPawn);
	if (!Character)
	{
		return;
	}
	const URagnarokAnimInstance* AnimInstance = Character->GetRagnarokAnimInstance();
	if (!AnimInstance || !ShieldVisualInfo.ShieldDownAnimSequence)
	{
		return;
	}
	Character->GetAnimInstance()->PlayAnimationOverride(
	ShieldVisualInfo.ShieldDownAnimSequence, "DefaultSlot", 1, 0);
	
	if (GetShieldFlipbook(Character))
	{
		SetAndPlayFlipbookAnimation(GetShieldFlipbook(Character), false, ShieldVisualInfo.ShieldDownFlipbook);
	}
	PlayCameraShake(ShieldVisualInfo.ShieldDownCameraShake);
	PlaySoundAtPawnLocation(ShieldVisualInfo.ShieldDownSound);

	if (USphereComponent* ShieldSphereComponent = GetShieldSphere(Character))
	{
		ShieldSphereComponent->SetCollisionEnabled(ECollisionEnabled::NoCollision);
		ShieldSphereComponent->SetCollisionResponseToAllChannels(ECR_Ignore);
		
		ShieldSphereComponent->OnComponentBeginOverlap.RemoveAll(this);
	}
	GetWorld()->GetTimerManager().ClearTimer(EndAbilityTimer);
}

void UShieldAbility::OnShieldUpAnimEnded(bool bCompleted)
{
	APawn* AvatarPawn = GetCurrentAbilityInfo().AvatarPawn;
	if (!AvatarPawn)
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

	if (USphereComponent* ShieldSphereComponent = GetShieldSphere(Character))
	{
		ShieldSphereComponent->SetCollisionEnabled(ECollisionEnabled::QueryAndPhysics);
		ShieldSphereComponent->SetCollisionResponseToAllChannels(ECR_Block);
		
		ShieldSphereComponent->OnComponentBeginOverlap.AddDynamic(this, &ThisClass::OnShieldBeginOverlap);
	}
	GetWorld()->GetTimerManager().SetTimer(EndAbilityTimer, this, &ThisClass::EndAbility, MaxAbilityLength);
	
	if (GetShieldFlipbook(Character))
	{
		SetAndPlayFlipbookAnimation(GetShieldFlipbook(Character), true, ShieldVisualInfo.ShieldActiveFlipbook);
	}
}

void UShieldAbility::OnShieldBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,
	UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	// TODO : Shield protection impl
}

void UShieldAbility::SetAndPlayFlipbookAnimation(UPaperFlipbookComponent* PaperFlipbookComponent, bool bIsLopping,
	UPaperFlipbook* Flipbook)
{
	PaperFlipbookComponent->SetLooping(bIsLopping);
	PaperFlipbookComponent->SetFlipbook(Flipbook);
	PaperFlipbookComponent->Play();
}

UPaperFlipbookComponent* UShieldAbility::GetShieldFlipbook(const APawn* Pawn) const
{
	if (const IShieldBearerInterface* ShieldBearer = Cast<IShieldBearerInterface>(Pawn))
	{
		return ShieldBearer->GetShieldFlipbookComponent();
	}
	
	return nullptr;
}

USphereComponent* UShieldAbility::GetShieldSphere(const APawn* Pawn) const
{
	if (const IShieldBearerInterface* ShieldBearer = Cast<IShieldBearerInterface>(Pawn))
	{
		return ShieldBearer->GetShieldSphereComponent();
	}
	
	return nullptr;
}
