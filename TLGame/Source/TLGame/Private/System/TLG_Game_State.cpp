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
    int32 hours, minutes;

    Current_Time_Minutes += minutes_to_add;

    if (Current_Time_Minutes >= Max_Time_Minutes)  // if end of the day
        Current_Time_Minutes = Max_Time_Minutes;  // TODO: Trigger End Of Day Event

    Get_Current_Time(hours, minutes);

    On_Time_Updated.Broadcast(hours, minutes, minutes_to_add);
}
//------------------------------------------------------------------------------------------------------------
void ATLG_Game_State::Get_Current_Time(int32 &hours, int32 &minutes) const
{
    hours = Current_Time_Minutes / 60;
    minutes = Current_Time_Minutes % 60;
}
//------------------------------------------------------------------------------------------------------------