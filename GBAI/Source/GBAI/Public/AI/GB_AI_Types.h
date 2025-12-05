//------------------------------------------------------------------------------------------------------------
#pragma once
//------------------------------------------------------------------------------------------------------------
#include <GameplayTagContainer.h>
#include "GB_AI_Types.generated.h"
//------------------------------------------------------------------------------------------------------------
USTRUCT() struct FSGB_AI_Payload_Test
{
	GENERATED_BODY()

	int STest_Param_Int = 0;

};
//------------------------------------------------------------------------------------------------------------
USTRUCT(BlueprintType) struct FGB_AI_Character_Stats_Base
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Stats") float Health_Max = 100.0f;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Stats") float Health_Curr = 100.0f;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Stats") float Health_Regen_Rate = 0.1f;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Stats") float Health_Regen_Delay = 5.0f;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Stats") float Stamina_Max = 100.0f;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Stats") float Stamina_Curr = 100.0f;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Stats") float Stamina_Regen_Rate = 5.0f;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Stats") float Stamina_Regen_Delay = 5.0f;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Stats") float Stamina_Drain_Rate = 10.0f;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Stats", meta = (ClampMin = "150.0", ClampMax = "1000.0") ) float Attack_Range = 150.0f;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Stats") float Movement_Speed_Run = 600.0f;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Stats") float Movement_Speed_Walk = 300.0f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Stats|Custom") TMap<FGameplayTag, float> Stats_Custom;

};
//------------------------------------------------------------------------------------------------------------
