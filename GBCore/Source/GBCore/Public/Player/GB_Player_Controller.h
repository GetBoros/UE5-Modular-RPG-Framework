//------------------------------------------------------------------------------------------------------------
#pragma once
//------------------------------------------------------------------------------------------------------------
#include "GameFramework/PlayerController.h"
#include "GB_Player_Controller.generated.h"
//------------------------------------------------------------------------------------------------------------
class UInputMappingContext;
class UInputAction;
struct FInputActionValue;
//------------------------------------------------------------------------------------------------------------
UCLASS() class GBCORE_API AGB_Player_Controller : public APlayerController
{
	GENERATED_BODY()
	
public:
	AGB_Player_Controller();

	virtual void BeginPlay();
	virtual void SetupInputComponent();

	void Handle_Move(const FInputActionValue &input_action_value);
	void Handle_Move_Completed(const FInputActionValue &input_action_value);

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Input") UInputMappingContext *Input_Mapping_Context;
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Input") UInputAction *Move_Action;
};
//------------------------------------------------------------------------------------------------------------
