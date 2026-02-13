//------------------------------------------------------------------------------------------------------------
#pragma once
//------------------------------------------------------------------------------------------------------------
#include <UObject/Interface.h>
#include <GameplayTagContainer.h>

#include <TLG_Interaction_Interface.generated.h>
//------------------------------------------------------------------------------------------------------------
UENUM(BlueprintType) enum class ETLG_Game_Flow_Option : uint8
{
    None,
    Continue,
    Restart_Level,
    Quit_Game,
    MainMenu
};
//------------------------------------------------------------------------------------------------------------
class UTLG_Data_Location;
struct FTLG_Location_Action;
//------------------------------------------------------------------------------------------------------------
UINTERFACE(MinimalAPI) class UTLG_Interaction_Interface : public UInterface
{
    GENERATED_BODY()
};
//------------------------------------------------------------------------------------------------------------
class TLGAME_API ITLG_Interaction_Interface
{
    GENERATED_BODY()

public:
    virtual void Location_Enter(UTLG_Data_Location *tlg_data_location) = 0;
    virtual void Location_Action(const FTLG_Location_Action &tlg_location_action) = 0;
    virtual void Request_Game_Over_Flow(const ETLG_Game_Flow_Option tlg_game_flow_option) = 0;
};
//------------------------------------------------------------------------------------------------------------
