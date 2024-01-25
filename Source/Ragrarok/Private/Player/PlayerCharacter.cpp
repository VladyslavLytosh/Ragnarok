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
	
	ShieldSphereComponent = CreateDefaultSubobject<USphereComponent>("ShieldSphereComponent");
	ShieldFlipbookComponent = CreateDefaultSubobject<UPaperFlipbookComponent>("ShieldFlipbookComponent");
	
	ShieldSphereComponent->SetupAttachment(GetSprite());
	ShieldSphereComponent->SetCollisionEnabled(ECollisionEnabled::NoCollision);
	ShieldSphereComponent->SetCollisionResponseToAllChannels(ECR_Ignore);
	
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

void APlayerCharacter::SetCurrentEquippedWeapon(TSubclassOf<UBaseWeaponInstance> CurrentEquippedWeaponClass)
{
	CurrentEquippedWeapon = NewObject<UBaseWeaponInstance>(this, CurrentEquippedWeaponClass);
}
