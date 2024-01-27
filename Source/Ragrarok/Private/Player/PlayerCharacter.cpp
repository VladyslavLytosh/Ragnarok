// Copyright by Suspended Team.


#include "Player/PlayerCharacter.h"
#include "EnhancedInputComponent.h"
#include "PaperFlipbookComponent.h"
#include "Components/SphereComponent.h"
#include "Input/RagnarokInputComponent.h"
#include "Weapons/BaseWeaponInstance.h"

APlayerCharacter::APlayerCharacter()
{
	//PrimaryActorTick.bCanEverTick = true;

	RagnarokInputComponent = CreateDefaultSubobject<URagnarokInputComponent>(TEXT("RagnarokInputComponent"));
	
	ShieldFlipbookComponent = CreateDefaultSubobject<UPaperFlipbookComponent>("ShieldFlipbookComponent");
	
	ShieldFlipbookComponent->SetupAttachment(GetSprite());
	ShieldFlipbookComponent->SetWorldScale3D(FVector(2,2,2));
}

void APlayerCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);
	check(RagnarokInputComponent);

	UEnhancedInputComponent* EnhancedInputComponent = Cast<UEnhancedInputComponent>(InputComponent);
	check(EnhancedInputComponent);
	
	RagnarokInputComponent->InitializePlayerInput(EnhancedInputComponent);
}
