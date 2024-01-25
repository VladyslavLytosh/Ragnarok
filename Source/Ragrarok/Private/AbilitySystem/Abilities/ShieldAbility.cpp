// Copyright by Suspended Team.


#include "AbilitySystem/Abilities/ShieldAbility.h"

#include "PaperFlipbookComponent.h"
#include "PaperZDAnimInstance.h"
#include "Characters/BaseCharacter.h"
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

	if (Character->GetPaperFlipbookComponent())
	{
		SetAndPlayFlipbookAnimation(Character->GetPaperFlipbookComponent(), false, ShieldVisualInfo.ShieldUpFlipbook);
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
	
	if (Character->GetPaperFlipbookComponent())
	{
		SetAndPlayFlipbookAnimation(Character->GetPaperFlipbookComponent(), false, ShieldVisualInfo.ShieldDownFlipbook);
	}

	if (USphereComponent* ShieldSphereComponent = Character->GetShieldSphereComponent())
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

	if (USphereComponent* ShieldSphereComponent = Character->GetShieldSphereComponent())
	{
		ShieldSphereComponent->SetCollisionEnabled(ECollisionEnabled::QueryAndPhysics);
		ShieldSphereComponent->SetCollisionResponseToAllChannels(ECR_Block);
		
		ShieldSphereComponent->OnComponentBeginOverlap.AddDynamic(this, &ThisClass::OnShieldBeginOverlap);
	}
	GetWorld()->GetTimerManager().SetTimer(EndAbilityTimer, this, &ThisClass::EndAbility, MaxAbilityLength);
	
	if (Character->GetPaperFlipbookComponent())
	{
		SetAndPlayFlipbookAnimation(Character->GetPaperFlipbookComponent(), true, ShieldVisualInfo.ShieldActiveFlipbook);
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
