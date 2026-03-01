//------------------------------------------------------------------------------------------------------------
#include <StateTree/Conditions/TLG_STC_Story_Flag_Check.h>
#include "StateTreeExecutionContext.h"
#include <Subsystems/TLG_Subsystem_Story.h>
//------------------------------------------------------------------------------------------------------------




// UTLG_STC_Story_Flag_Check
bool UTLG_STC_Story_Flag_Check::TestCondition(FStateTreeExecutionContext &context) const
{
    bool is_flag_added;
    UGameInstance *game_instance;
    UTLG_Subsystem_Story *story_subsystem;

    game_instance = context.GetWorld()->GetGameInstance();
    if (game_instance == 0)
        return false;

    story_subsystem = game_instance->GetSubsystem<UTLG_Subsystem_Story>();
    if (story_subsystem == 0)
        return false;

    is_flag_added = story_subsystem->Has_Story_Flag(Flag);
    if (is_flag_added == true)
        return false;  // Flag exists don`t pass condition
    else
        return true;  // Flag not exist pass condition
}
//------------------------------------------------------------------------------------------------------------
bool UTLG_STC_Story_Flag_Check::ReceiveTestCondition() const
{
	return true;
}
//------------------------------------------------------------------------------------------------------------
