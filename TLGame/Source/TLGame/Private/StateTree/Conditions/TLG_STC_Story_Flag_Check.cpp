//------------------------------------------------------------------------------------------------------------
#include <StateTree/Conditions/TLG_STC_Story_Flag_Check.h>
#include "StateTreeExecutionContext.h"
#include <Subsystems/TLG_Subsystem_Story.h>
//------------------------------------------------------------------------------------------------------------




// UTLG_STC_Story_Flag_Check
bool UTLG_STC_Story_Flag_Check::TestCondition(FStateTreeExecutionContext &context) const
{
    bool is_tree_seccceeded;
    bool is_flag_added;
    UGameInstance *game_instance;
    UTLG_Subsystem_Story *story_subsystem;

    is_tree_seccceeded = false;
    game_instance = context.GetWorld()->GetGameInstance();
    if (game_instance == 0)
        return is_tree_seccceeded;  // On State Failed

    story_subsystem = game_instance->GetSubsystem<UTLG_Subsystem_Story>();
    if (story_subsystem == 0)
        return is_tree_seccceeded;  // On State Failed

    is_flag_added = story_subsystem->Has_Story_Flag(Flag);
    if (is_flag_added == true)
        is_tree_seccceeded = false;  // On State Failed
    else
        is_tree_seccceeded = true;  // On State Failed Seccceeded

    return is_tree_seccceeded;
}
//------------------------------------------------------------------------------------------------------------
bool UTLG_STC_Story_Flag_Check::ReceiveTestCondition() const
{
	return true;
}
//------------------------------------------------------------------------------------------------------------
