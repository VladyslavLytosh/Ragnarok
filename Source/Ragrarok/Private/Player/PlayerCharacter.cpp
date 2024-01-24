// Copyright by Suspended Team.


#include "Player/PlayerCharacter.h"
#include "EnhancedInputComponent.h"
#include "Input/RagnarokInputComponent.h"

APlayerCharacter::APlayerCharacter()
{
	//PrimaryActorTick.bCanEverTick = true;

	RagnarokInputComponent = CreateDefaultSubobject<URagnarokInputComponent>(TEXT("RagnarokInputComponent"));
}

void APlayerCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);
	check(RagnarokInputComponent);

	UEnhancedInputComponent* EnhancedInputComponent = Cast<UEnhancedInputComponent>(InputComponent);
	check(EnhancedInputComponent);
	
	RagnarokInputComponent->InitializePlayerInput(EnhancedInputComponent);
}
