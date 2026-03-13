//------------------------------------------------------------------------------------------------------------
#pragma once
//------------------------------------------------------------------------------------------------------------
#include <Abilities/GameplayAbility.h>

#include <GBG_Gameplay_Ability.generated.h>
//------------------------------------------------------------------------------------------------------------
UCLASS() class GBGAMEPLAY_API UGBG_Gameplay_Ability : public UGameplayAbility
{
	GENERATED_BODY()

public:
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Input") int32 Input_ID = 0;  // 0 = No Input

};
//------------------------------------------------------------------------------------------------------------