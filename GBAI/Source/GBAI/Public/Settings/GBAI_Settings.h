//------------------------------------------------------------------------------------------------------------
#pragma once
//------------------------------------------------------------------------------------------------------------
#include "Engine/DeveloperSettings.h"
#include "GBAI_Settings.generated.h"
//------------------------------------------------------------------------------------------------------------
/**
 * Global Setting Project Settings
 * Config = Game означает save to DefaultGame.ini
 * defaultconfig can Edit in Project Settings
 */
UCLASS(Config = Game, defaultconfig, meta = (DisplayName = "GB AI Settings") ) class GBAI_API UGBAI_Settings : public UDeveloperSettings
{
    GENERATED_BODY()

public:
    UPROPERTY(Config, EditAnywhere, Category = "Debugging") bool Draw_Debug_Hunger = false;  // Show/Hide visual debuger at the bot head
    UPROPERTY(Config, EditAnywhere, Category = "Balancing") float Global_Hunger_Multiplier = 1.0f;  // If 2.0 starving faster
    UPROPERTY(Config, EditAnywhere, Category = "Balancing") float Global_Perception_Radius = 1500.0f;  // Radius for bots, to see items from subsystem
};
//------------------------------------------------------------------------------------------------------------