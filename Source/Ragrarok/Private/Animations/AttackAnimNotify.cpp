// Copyright by Suspended Team.


#include "Animations/AttackAnimNotify.h"

#include "Animations/RagnarokAnimInstance.h"

void UAttackAnimNotify::OnReceiveNotify_Implementation(UPaperZDAnimInstance* OwningInstance)
{
	Super::OnReceiveNotify_Implementation(OwningInstance);

	const URagnarokAnimInstance* RagnarokAnimInstance = Cast<URagnarokAnimInstance>(OwningInstance);
	if (!RagnarokAnimInstance)
	{
		UE_LOG(LogTemp,Error,TEXT("Ragnarok anim instance does not exist in AttackAnimNotify"));
		return;
	}

	if (RagnarokAnimInstance->AttackNotifyDelegate.IsBound())
	{
		RagnarokAnimInstance->AttackNotifyDelegate.Broadcast();
	}
}
