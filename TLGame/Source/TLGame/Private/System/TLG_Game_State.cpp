//------------------------------------------------------------------------------------------------------------
#include <System/TLG_Game_State.h>
//------------------------------------------------------------------------------------------------------------




// ATLG_Game_State
ATLG_Game_State::ATLG_Game_State()
{
	Current_Time_Minutes = 8 * 60;  // Start at 8:00 AM
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
