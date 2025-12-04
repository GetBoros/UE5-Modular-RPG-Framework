//------------------------------------------------------------------------------------------------------------
#pragma once
//------------------------------------------------------------------------------------------------------------
#include "GameFramework/Character.h"
#include "GB_AI_Character.generated.h"
//------------------------------------------------------------------------------------------------------------
class UInputComponent;
//------------------------------------------------------------------------------------------------------------
UCLASS() class GBAI_API AGB_AI_Character : public ACharacter
{
	GENERATED_BODY()

public:
	AGB_AI_Character();

	virtual void BeginPlay();
	virtual void Tick(float delta_time);
	virtual void SetupPlayerInputComponent(UInputComponent *player_input_component);

};
//------------------------------------------------------------------------------------------------------------
