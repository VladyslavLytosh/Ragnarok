// Copyright by Suspended Team.

#pragma once

#include "CoreMinimal.h"
#include "Components/PawnComponent.h"
#include "EnhancedInputComponent.h"
#include "RagnarokInputConfig.h"
#include "RagnarokInputComponent.generated.h"

UCLASS(ClassGroup=(Custom), meta=(BlueprintSpawnableComponent))
class RAGRAROK_API URagnarokInputComponent : public UPawnComponent
{
	GENERATED_BODY()

public:
	void InitializePlayerInput(UEnhancedInputComponent* PlayerInputComponent);

	UInputMappingContext* GetMappingContext() const {return  MappingContext;}
protected:
	void Input_AbilityInputTagPressed(FGameplayTag InputTag);
	void Input_AbilityInputTagReleased(FGameplayTag InputTag);
	
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category="Input")
	UInputMappingContext* MappingContext;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category="Input")
	URagnarokInputConfig* InputConfig;
private:
	template<class UserClass, typename PressedFuncType, typename ReleasedFuncType>
void BindAbilityActions(UEnhancedInputComponent* PlayerInputComponent,UserClass* Object, PressedFuncType PressedFunc, ReleasedFuncType ReleasedFunc, TArray<uint32>& BindHandles);

	template<class UserClass, typename FuncType>
	void BindNativeAction(UEnhancedInputComponent* PlayerInputComponent, const FGameplayTag& InputTag, ETriggerEvent TriggerEvent, UserClass* Object, FuncType Func, bool bLogIfNotFound);
};

template <class UserClass, typename PressedFuncType, typename ReleasedFuncType>
void URagnarokInputComponent::BindAbilityActions(UEnhancedInputComponent* PlayerInputComponent, UserClass* Object,
	PressedFuncType PressedFunc, ReleasedFuncType ReleasedFunc, TArray<uint32>& BindHandles)
{
	if (!PlayerInputComponent) return;
	
	for (const FRagnarokInputAction& Action : InputConfig->AbilityInputActions)
	{
		if (Action.InputAction && Action.InputTag.IsValid())
		{
			if (PressedFunc)
			{
				PlayerInputComponent->BindAction(Action.InputAction, ETriggerEvent::Triggered, Object, PressedFunc, Action.InputTag);
			}

			if (ReleasedFunc)
			{
				PlayerInputComponent->BindAction(Action.InputAction,ETriggerEvent::Completed, Object, ReleasedFunc, Action.InputTag);
			}
		}
	}
}

template <class UserClass, typename FuncType>
void URagnarokInputComponent::BindNativeAction(UEnhancedInputComponent* PlayerInputComponent, const FGameplayTag& InputTag,
	ETriggerEvent TriggerEvent, UserClass* Object, FuncType Func, bool bLogIfNotFound)
{
	if (!PlayerInputComponent) return;
	
	if (const UInputAction* IA = InputConfig->FindNativeInputActionForTag(InputTag, bLogIfNotFound))
	{
		PlayerInputComponent->BindAction(IA, TriggerEvent, Object, Func);
	}
}	

