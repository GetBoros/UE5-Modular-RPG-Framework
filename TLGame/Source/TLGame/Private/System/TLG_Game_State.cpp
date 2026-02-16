//------------------------------------------------------------------------------------------------------------
#include <System/TLG_Game_State.h>
//------------------------------------------------------------------------------------------------------------




// ATLG_Game_State
ATLG_Game_State::ATLG_Game_State()
{
	Current_Time_Minutes = 8 * 60;  // Start at 8:00 AM
	TLG_Game_State = ETLG_Game_State::Game;
}
//------------------------------------------------------------------------------------------------------------
void ATLG_Game_State::Broadcast_Game_Time_Current()
{
    constexpr int32 minutes_to_add = 0;

    Advance_Time(minutes_to_add);
    
    On_Updated_Day.Broadcast(Get_Current_Day() );
}
//------------------------------------------------------------------------------------------------------------
void ATLG_Game_State::Game_Menu_Paused()
{
    if (TLG_Game_State != ETLG_Game_State::Menu_Pause)  // Set menu pause game state if already not in pause menu
    {
        TLG_Game_State = ETLG_Game_State::Menu_Pause;

        On_Game_Menu_Paused.Broadcast();
    }
    else
        Game_Resume();  // if already in Menu Pause resume game

}
//------------------------------------------------------------------------------------------------------------
void ATLG_Game_State::Game_Resume()
{
    if (TLG_Game_State == ETLG_Game_State::Game_Over || TLG_Game_State == ETLG_Game_State::Game_Demo_Completed)
        return;  // return if game over or game completed

    TLG_Game_State = ETLG_Game_State::Game;

    On_Game_Resumed.Broadcast();
}
//------------------------------------------------------------------------------------------------------------
void ATLG_Game_State::Game_Over()
{
	TLG_Game_State = ETLG_Game_State::Game_Over;

	On_Game_Over.Broadcast();
}
//------------------------------------------------------------------------------------------------------------
void ATLG_Game_State::Game_Demo_Completed()
{
    TLG_Game_State = ETLG_Game_State::Game_Demo_Completed;

    On_Game_Demo_Completed.Broadcast();
}
//------------------------------------------------------------------------------------------------------------
void ATLG_Game_State::Advance_Time(int32 minutes_to_add)
{
    int32 hours, minutes, days_passed;

    // 1.0. Add Mins
    Current_Time_Minutes += minutes_to_add;

    // 1.1. Days || Calculate how many full days passed and reset minutes if true
    days_passed = Current_Time_Minutes / Max_Time_Minutes;
    if (days_passed > 0)
    {
        Current_Time_Day += days_passed;
        Current_Time_Minutes = Current_Time_Minutes % Max_Time_Minutes;

        On_Updated_Day.Broadcast(Current_Time_Day);

        if (Current_Time_Day > Max_Demo_Days)
        {
            Game_Demo_Completed();  // !!! TEMP Change on Congratulation or Demo Completed

            return; // Выходим, не обновляем время дальше
        }
    }

    // 1.2.  Update Game Time
    hours = Current_Time_Minutes / 60;
    minutes = Current_Time_Minutes % 60;

    On_Updated_Time.Broadcast(hours, minutes, minutes_to_add);
}
//------------------------------------------------------------------------------------------------------------
int32 ATLG_Game_State::Get_Current_Day() const
{
    return Current_Time_Day;
}
//------------------------------------------------------------------------------------------------------------
