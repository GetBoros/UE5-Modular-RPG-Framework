//------------------------------------------------------------------------------------------------------------
#pragma once
//------------------------------------------------------------------------------------------------------------
#include "Interfaces/GB_AI_Target_Interface.h"
#include "Interfaces/GB_Character_Interface.h"

#include "GameFramework/Character.h"
//------------------------------------------------------------------------------------------------------------
#include "GB_Player_Character.generated.h"
//------------------------------------------------------------------------------------------------------------
class UInputComponent;
//------------------------------------------------------------------------------------------------------------
UCLASS() class GBCHARACTER_API AGB_Player_Character : public ACharacter, public IGB_Character_Interface, public IGB_AI_Target_Interface
{
	GENERATED_BODY()

public:
	AGB_Player_Character();

	virtual void BeginPlay();
	virtual void Tick(float delta_time);
	virtual void SetupPlayerInputComponent(UInputComponent *player_input_component);

	virtual void Move_Implementation(const FVector2D &world_direction, float scale_value) override;
	virtual FGB_Types_Health Get_Types_Health_Implementation();
	virtual FVector Get_Target_Location_Implementation();

protected:
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Attributes") float Health_Max = 100.0f;
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Attributes") float Health_Current = 100.0f;
};
//------------------------------------------------------------------------------------------------------------
