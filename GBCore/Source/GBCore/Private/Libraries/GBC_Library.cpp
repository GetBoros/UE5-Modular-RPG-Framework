//------------------------------------------------------------------------------------------------------------
#include <Libraries/GBC_Library.h>
//------------------------------------------------------------------------------------------------------------
#define LOCTEXT_NAMESPACE "GBUI_Library"
//------------------------------------------------------------------------------------------------------------




// UGBC_Library
FText UGBC_Library::Format_Time_From_Minutes(int32 minutes)
{
    // Magic numbers moved to constants for readability
    const int32 minutes_in_hour = 60;
    const int32 minutes_in_day = 1440;   // 24 * 60
    const int32 minutes_in_month = 43200; // 30 * 1440

    // 1. Check Months (Clean division)
    if (minutes >= minutes_in_month && (minutes % minutes_in_month == 0))
        return FText::Format(LOCTEXT("Time_Format_Months", "{0}mon"), FText::AsNumber(minutes / minutes_in_month) );

    // 2. Check Days
    if (minutes >= minutes_in_day && (minutes % minutes_in_day == 0))
        return FText::Format(LOCTEXT("Time_Format_Days", "{0}d"), FText::AsNumber(minutes / minutes_in_day) );

    // 3. Check Hours
    if (minutes >= minutes_in_hour && (minutes % minutes_in_hour == 0) )
        return FText::Format(LOCTEXT("Time_Format_Hours", "{0}h"), FText::AsNumber(minutes / minutes_in_hour) );

    // 4. Default Minutes
    return FText::Format(LOCTEXT("Time_Format_Minutes", "{0}min"), FText::AsNumber(minutes) );
}
//------------------------------------------------------------------------------------------------------------




//------------------------------------------------------------------------------------------------------------
#undef LOCTEXT_NAMESPACE
//------------------------------------------------------------------------------------------------------------